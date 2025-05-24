namespace PipelineSystem.Services;

using System;
using System.Collections.Generic;
using System.Collections.Concurrent;
using System.Threading;
using System.Threading.Tasks;
using System.Text;
using PipelineSystem.Interfaces;
using PipelineSystem.Models;
using PipelineSystem.Infrastructure;
using System.Threading.Channels;
using PipelineSystem.Services.Processors;
using System.Diagnostics;

public class PipelineCoordinator : IDisposable
{
    private const int QueueMaxSize = 100;
    private const int MaxConcurrentProcessors = 5;
    
    private readonly PipelineConfig _config;
    private readonly ILogger _logger;
    private readonly List<StudentEmitter> _students = new();
    private readonly List<CiCdProcessor> _ciCdProcessors = new();
    private readonly List<TeacherProcessor> _teachers = new();
    
    private readonly BlockingCollection<CommitEvent> _ciCdQueue = new(QueueMaxSize);
    private readonly BlockingCollection<CommitEvent> _teacherQueue = new(QueueMaxSize);
    private readonly BlockingCollection<CommitEvent> _returnQueue = new(QueueMaxSize);
    
    private readonly ProcessorPool<CommitEvent> _cicdPool;
    private readonly ProcessorPool<CommitEvent> _teacherPool;
    private readonly CancellationTokenSource _cts = new();
    private readonly StatisticsManager _statistics;
    private bool _isDisposed;

    public PipelineCoordinator(PipelineConfig config, ILogger logger)
    {
        _config = config;
        _logger = logger;
        _statistics = new StatisticsManager(logger, _ciCdQueue, _teacherQueue, _returnQueue);
        
        _cicdPool = new ProcessorPool<CommitEvent>(
            MaxConcurrentProcessors,
            commit => ProcessCiCdEvent(commit),
            _ciCdQueue,
            logger
        );
        
        _teacherPool = new ProcessorPool<CommitEvent>(
            config.NumberOfTeachers,
            commit => ProcessTeacherEvent(commit),
            _teacherQueue,
            logger
        );
    }

    public void Start()
    {
        _logger.LogEvent("Запуск координатора...");
        InitializeComponents(_config);
        _logger.LogEvent($"Инициализировано: {_students.Count} студентов, {_ciCdProcessors.Count} CI/CD процессоров, {_teachers.Count} преподавателей");

        foreach (var student in _students)
        {
            student.Start();
        }
    
        _cicdPool.Start();
        _teacherPool.Start();
    }

    private void InitializeComponents(PipelineConfig config)
    {
        // Создаем студентов
        for (int i = 0; i < config.NumberOfStudents; i++)
        {
            var student = new StudentEmitter(
                $"Student_{i}", 
                _logger, 
                _ciCdQueue,
                this,
                _cts.Token,
                config.StudentEmitFrequencyMs,
                config.RandomDelayMaxMs
            );
            _students.Add(student);
        }

        // Создаем CI/CD процессоры
        for (int i = 0; i < config.NumberOfTesters; i++)
        {
            var ciCd = new CiCdProcessor($"CiCd_{i}", _logger, _teacherQueue, _returnQueue);
            ciCd.Configure(config.TestProcessingTimeMs, config.RandomDelayMaxMs);
            _ciCdProcessors.Add(ciCd);
        }

        // Создаем преподавателей
        for (int i = 0; i < config.NumberOfTeachers; i++)
        {
            var teacher = new TeacherProcessor($"Teacher_{i}", _logger, _returnQueue);
            teacher.Configure(config.TeacherProcessingTimeMs, config.RandomDelayMaxMs);
            _teachers.Add(teacher);
        }
    }

    private void ProcessCiCdEvent(CommitEvent commit)
    {
        var processor = _ciCdProcessors[Random.Shared.Next(_ciCdProcessors.Count)];
        processor.Process(commit);
        _statistics.UpdateCiCdStat(processor.Id, commit.TestsPassed);
    }

    private void ProcessTeacherEvent(CommitEvent commit)
    {
        TeacherProcessor? availableTeacher = null;
        
        while (availableTeacher == null)
        {
            // Ищем свободного преподавателя
            availableTeacher = _teachers
                .Where(t => !t.IsBusy)
                .OrderBy(_ => Random.Shared.Next())
                .FirstOrDefault();

            if (availableTeacher == null)
            {
                Thread.Sleep(100); 
                continue;
            }

            if (!availableTeacher.TryProcess(commit))
            {
                availableTeacher = null;
                continue;
            }

            _statistics.UpdateTeacherStat(availableTeacher.Id, commit.NeedsRevision);
        }
    }

    public void UpdateStudentStats(string studentId)
    {
        _statistics.UpdateStudentStat(studentId);
    }

    public void Dispose()
    {
        if (_isDisposed) return;

        try
        {
            _logger.LogEvent("Начало процесса завершения работы...");
            _cts.Cancel();

            var timeout = TimeSpan.FromSeconds(5);
            var sw = Stopwatch.StartNew();

            Task.WaitAll(new[] 
            {
                _cicdPool.StopAsync(timeout),
                _teacherPool.StopAsync(timeout)
            }, timeout);

            _ciCdQueue.Dispose();
            _teacherQueue.Dispose();
            _returnQueue.Dispose();

            _statistics.LogFinalStatisticsAsync().Wait();
            
            _logger.LogEvent($"Все задачи успешно завершены за {sw.ElapsedMilliseconds}мс");
        }
        catch (Exception ex) when (ex is not OperationCanceledException)
        {
            _logger.LogEvent($"Ошибка при завершении работы: {ex.Message}");
        }
        finally
        {
            _logger.LogEvent("Координатор остановлен");
            _isDisposed = true;
        }
    }
} 