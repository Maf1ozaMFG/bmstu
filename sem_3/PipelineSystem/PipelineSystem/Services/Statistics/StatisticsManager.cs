using PipelineSystem.Interfaces;
using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using PipelineSystem.Models;

public class StatisticsManager
{
    private readonly ConcurrentDictionary<string, int> _studentStats = new();
    private readonly ConcurrentDictionary<string, (int Total, int Returned)> _teacherStats = new();
    private readonly ConcurrentDictionary<string, (int Total, int Failed)> _cicdStats = new();
    private readonly ILogger _logger;
    private int _totalCommits;
    private int _totalProcessed;
    private int _totalFailed;
    private int _totalReturned;

    // Статистика очередей
    private readonly ConcurrentDictionary<string, QueueStats> _queueStats = new();
    private readonly Timer _queueMonitorTimer;
    private readonly DateTime _startTime;

    private class QueueStats
    {
        public int Current { get; set; }
        public int Max { get; set; }
        public long TotalMeasurements { get; set; }
        public long SumLength { get; set; }
        
        public double AverageLength => TotalMeasurements > 0 
            ? (double)SumLength / TotalMeasurements 
            : 0;
    }

    public StatisticsManager(
        ILogger logger,
        BlockingCollection<CommitEvent> cicdQueue,
        BlockingCollection<CommitEvent> teacherQueue,
        BlockingCollection<CommitEvent> returnQueue)
    {
        _logger = logger;
        _startTime = DateTime.Now;
        
        _queueStats["CI/CD"] = new QueueStats();
        _queueStats["Teacher"] = new QueueStats();
        _queueStats["Return"] = new QueueStats();

        // Мониторинг каждые 100мс
        _queueMonitorTimer = new Timer(_ => UpdateQueueStats(
            ("CI/CD", cicdQueue),
            ("Teacher", teacherQueue),
            ("Return", returnQueue)
        ), null, TimeSpan.Zero, TimeSpan.FromMilliseconds(100));
    }

    private void UpdateQueueStats(params (string Name, BlockingCollection<CommitEvent> Queue)[] queues)
    {
        foreach (var (name, queue) in queues)
        {
            var count = queue.Count;
            var stats = _queueStats[name];
            
            stats.Current = count;
            stats.Max = Math.Max(stats.Max, count);
            stats.SumLength += count;
            stats.TotalMeasurements++;
        }
    }

    public void InitializeStats(IEnumerable<string> studentIds, 
                              IEnumerable<string> cicdIds, 
                              IEnumerable<string> teacherIds)
    {
        foreach (var id in studentIds) _studentStats[id] = 0;
        foreach (var id in cicdIds) _cicdStats[id] = (0, 0);
        foreach (var id in teacherIds) _teacherStats[id] = (0, 0);
    }

    public void UpdateStudentStat(string studentId) 
    {
        lock (_studentStats)
        {
            _studentStats.TryGetValue(studentId, out int value);
            _studentStats[studentId] = value + 1;
            Interlocked.Increment(ref _totalCommits);
        }
    }

    public void UpdateTeacherStat(string teacherId, bool returnedForRevision)
    {
        lock (_teacherStats)
        {
            var (total, returned) = _teacherStats.GetValueOrDefault(teacherId);
            _teacherStats[teacherId] = (total + 1, returned + (returnedForRevision ? 1 : 0));
            if (returnedForRevision)
            {
                Interlocked.Increment(ref _totalReturned);
            }
        }
    }

    public void UpdateCiCdStat(string cicdId, bool testsPassed)
    {
        lock (_cicdStats)
        {
            var (total, failed) = _cicdStats.GetValueOrDefault(cicdId);
            _cicdStats[cicdId] = (total + 1, failed + (testsPassed ? 0 : 1));
            Interlocked.Increment(ref _totalProcessed);
            if (!testsPassed)
            {
                Interlocked.Increment(ref _totalFailed);
            }
        }
    }

    public async Task LogFinalStatisticsAsync()
    {
        _queueMonitorTimer.Dispose();
        var runTime = DateTime.Now - _startTime;
        
        var stats = new StringBuilder();
        stats.AppendLine("\n=== ИТОГОВАЯ СТАТИСТИКА РАБОТЫ СИСТЕМЫ ===\n");
        
        // Общая статистика
        stats.AppendLine("ОБЩИЕ ПОКАЗАТЕЛИ:");
        stats.AppendLine($"Всего создано коммитов: {_totalCommits}");
        stats.AppendLine($"Всего обработано CI/CD: {_totalProcessed}");
        stats.AppendLine($"Успешных сборок: {_totalProcessed - _totalFailed} ({(_totalProcessed > 0 ? (double)(_totalProcessed - _totalFailed) / _totalProcessed * 100 : 0):F2}%)");
        stats.AppendLine($"Неудачных сборок: {_totalFailed} ({(_totalProcessed > 0 ? (double)_totalFailed / _totalProcessed * 100 : 0):F2}%)");
        
        // Статистика по студентам
        stats.AppendLine("\nСТАТИСТИКА ПО СТУДЕНТАМ:");
        var avgCommitsPerStudent = _totalCommits / (double)_studentStats.Count;
        stats.AppendLine($"Среднее количество коммитов на студента: {avgCommitsPerStudent:F2}");
        
        var topStudents = _studentStats
            .OrderByDescending(x => x.Value)
            .Take(5);
        
        stats.AppendLine("\nТоп-5 самых активных студентов:");
        foreach (var (studentId, commits) in topStudents)
        {
            stats.AppendLine($"{studentId}: {commits} коммитов");
        }
        
        // Статистика по CI/CD
        stats.AppendLine("\nСТАТИСТИКА ПО CI/CD ПРОЦЕССОРАМ:");
        foreach (var (cicdId, (total, failed)) in _cicdStats.OrderBy(x => x.Key))
        {
            var successRate = total > 0 ? (double)(total - failed) / total * 100 : 0;
            stats.AppendLine($"\n{cicdId}:");
            stats.AppendLine($"  Обработано коммитов: {total}");
            stats.AppendLine($"  Успешных сборок: {total - failed} ({successRate:F2}%)");
            stats.AppendLine($"  Неудачных сборок: {failed} ({(total > 0 ? (double)failed / total * 100 : 0):F2}%)");
        }
        
        // Статистика по преподавателям
        stats.AppendLine("\nСТАТИСТИКА ПО ПРЕПОДАВАТЕЛЯМ:");
        foreach (var (teacherId, (total, returned)) in _teacherStats.OrderBy(x => x.Key))
        {
            var returnRate = total > 0 ? (double)returned / total * 100 : 0;
            stats.AppendLine($"\n{teacherId}:");
            stats.AppendLine($"  Проверено коммитов: {total}");
            stats.AppendLine($"  Возвращено на доработку: {returned}");
            stats.AppendLine($"  Процент возврата: {returnRate:F2}%");
        }

        // Добавляем статистику очередей
        stats.AppendLine("\nСТАТИСТИКА ОЧЕРЕДЕЙ:");
        foreach (var (name, queueStats) in _queueStats)
        {
            stats.AppendLine($"\n{name}:");
            stats.AppendLine($"  Текущая длина: {queueStats.Current}");
            stats.AppendLine($"  Максимальная длина: {queueStats.Max}");
            stats.AppendLine($"  Средняя длина: {queueStats.AverageLength:F2}");
        }

        stats.AppendLine($"\nВремя работы системы: {runTime:hh\\:mm\\:ss\\.fff}");
        
        await _logger.LogStatisticsAsync(stats.ToString());
    }
} 