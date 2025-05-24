using System;
using System.Threading;
using System.Threading.Tasks;
using System.Threading.Channels;
using PipelineSystem.Models;
using PipelineSystem.Interfaces;
using PipelineSystem.Services;
using System.Collections.Concurrent;

public class StudentEmitter
{
    private readonly ILogger _logger;
    private readonly BlockingCollection<CommitEvent> _outputQueue;
    private readonly PipelineCoordinator _coordinator;
    private readonly CancellationToken _cancellationToken;
    private readonly int _personalEmitFrequencyMs;
    private readonly int _randomDelayMaxMs;
    
    public string Id { get; }

    public StudentEmitter(
        string id, 
        ILogger logger, 
        BlockingCollection<CommitEvent> outputQueue,
        PipelineCoordinator coordinator,
        CancellationToken cancellationToken,
        int baseEmitFrequencyMs,
        int randomDelayMaxMs)
    {
        Id = id;
        _logger = logger;
        _outputQueue = outputQueue;
        _coordinator = coordinator;
        _cancellationToken = cancellationToken;
        _randomDelayMaxMs = randomDelayMaxMs;
        
        var multiplier = 0.5 + Random.Shared.NextDouble();
        _personalEmitFrequencyMs = (int)(baseEmitFrequencyMs * multiplier);
        
        _logger.LogEvent($"Студент {Id} будет создавать коммиты каждые {_personalEmitFrequencyMs}мс");
    }

    public void Start()
    {
        var thread = new Thread(() => 
        {
            while (!_cancellationToken.IsCancellationRequested)
            {
                var commitId = GenerateCommitId();
                var commit = new CommitEvent(Id, commitId);
                
                _logger.LogEvent($"Студент {Id} создал коммит {commitId}");
                _outputQueue.Add(commit);
                _coordinator.UpdateStudentStats(Id);
                
                Thread.Sleep(_personalEmitFrequencyMs + Random.Shared.Next(_randomDelayMaxMs));
            }
        });
        thread.Start();
    }

    private string GenerateCommitId()
    {
        byte[] bytes = new byte[4];
        Random.Shared.NextBytes(bytes);
        return Convert.ToHexString(bytes).ToLower();
    }
} 