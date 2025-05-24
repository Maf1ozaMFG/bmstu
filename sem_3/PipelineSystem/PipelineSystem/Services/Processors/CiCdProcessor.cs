namespace PipelineSystem.Services.Processors;

using System;
using System.Threading;
using System.Threading.Tasks;
using PipelineSystem.Interfaces;
using PipelineSystem.Models;
using System.Threading.Channels;
using System.Collections.Concurrent;

public class CiCdProcessor : BaseProcessor<CommitEvent>
{
    private readonly BlockingCollection<CommitEvent> _outputQueue;
    private readonly BlockingCollection<CommitEvent> _returnQueue;

    public CiCdProcessor(
        string id,
        ILogger logger,
        BlockingCollection<CommitEvent> outputQueue,
        BlockingCollection<CommitEvent> returnQueue) : base(id, logger)
    {
        _outputQueue = outputQueue;
        _returnQueue = returnQueue;
    }

    public void Process(CommitEvent commit)
    {
        _logger.LogEvent($"CI/CD {Id} начал обработку коммита {commit.CommitHash}");
        
        Thread.Sleep(_processingTimeMs + Random.Shared.Next(_randomDelayMaxMs));
        
        commit.TestsPassed = Random.Shared.NextDouble() <= 0.7;
        
        if (commit.TestsPassed)
        {
            _outputQueue.Add(commit);
            _logger.LogEvent($"CI/CD {Id} отправил коммит {commit.CommitHash} преподавателю | Тесты прошли");
        }
        else
        {
            _returnQueue.Add(commit);
            _logger.LogEvent($"CI/CD {Id} вернул коммит {commit.CommitHash} студенту | Тесты не прошли");
        }
    }
}