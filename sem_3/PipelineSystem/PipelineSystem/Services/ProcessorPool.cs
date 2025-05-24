using System;
using System.Collections.Generic;
using System.Threading;
using System.Threading.Tasks;
using PipelineSystem.Interfaces;
using System.Threading.Channels;
using System.Collections.Concurrent;

public class ProcessorPool<T>
{
    private readonly int _maxWorkers;
    private readonly Action<T> _processor;
    private readonly BlockingCollection<T> _inputQueue;
    private readonly ILogger _logger;
    private readonly List<Thread> _workerThreads = new();
    private volatile bool _isRunning = true;
    
    public ProcessorPool(
        int maxWorkers,
        Action<T> processor,
        BlockingCollection<T> inputQueue,
        ILogger logger)
    {
        _maxWorkers = maxWorkers;
        _processor = processor;
        _inputQueue = inputQueue;
        _logger = logger;
    }
    
    public void Start()
    {
        for (int i = 0; i < _maxWorkers; i++)
        {
            var thread = new Thread(() => ProcessItems());
            _workerThreads.Add(thread);
            thread.Start();
        }
    }
    
    private void ProcessItems()
    {
        while (_isRunning)
        {
            try 
            {
                if (_inputQueue.TryTake(out var item, 100))
                {
                    _processor(item);
                }
            }
            catch (Exception ex)
            {
                _logger.LogEvent($"Ошибка обработки: {ex.Message}");
            }
        }
    }

    public Task StopAsync(TimeSpan timeout)
    {
        _isRunning = false;
        return Task.WhenAll(_workerThreads.Select(t => Task.Run(() => t.Join((int)timeout.TotalMilliseconds))));
    }
}