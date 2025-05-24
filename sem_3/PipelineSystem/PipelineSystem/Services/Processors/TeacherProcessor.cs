namespace PipelineSystem.Services.Processors;

using System;
using System.Threading;
using System.Threading.Tasks;
using System.Threading.Channels;
using PipelineSystem.Models;
using PipelineSystem.Interfaces;
using System.Collections.Concurrent;

public class TeacherProcessor : BaseProcessor<CommitEvent>
{
    private readonly BlockingCollection<CommitEvent> _returnQueue;
    private volatile bool _isBusy;
    private readonly object _lock = new();

    public TeacherProcessor(
        string id,
        ILogger logger,
        BlockingCollection<CommitEvent> returnQueue) : base(id, logger)
    {
        _returnQueue = returnQueue;
        _isBusy = false;
    }

    public bool TryProcess(CommitEvent commit)
    {
        lock (_lock)
        {
            if (_isBusy) return false;
            _isBusy = true;
        }

        try
        {
            _logger.LogEvent($"Преподаватель {Id} начал проверку коммита {commit.CommitHash}");
            
            Thread.Sleep(_processingTimeMs + Random.Shared.Next(_randomDelayMaxMs));
            
            commit.NeedsRevision = Random.Shared.NextDouble() <= 0.3;
            
            if (commit.NeedsRevision)
            {
                _returnQueue.Add(commit);
                _logger.LogEvent($"Преподаватель {Id} вернул коммит {commit.CommitHash} на доработку");
            }
            else
            {
                _logger.LogEvent($"Преподаватель {Id} принял коммит {commit.CommitHash}");
            }

            return true;
        }
        finally
        {
            lock (_lock)
            {
                _isBusy = false;
            }
        }
    }

    public bool IsBusy => _isBusy;
}