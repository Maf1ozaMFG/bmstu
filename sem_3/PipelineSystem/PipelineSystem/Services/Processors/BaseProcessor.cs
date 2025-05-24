using PipelineSystem.Interfaces;

public abstract class BaseProcessor<T>
{
    protected readonly ILogger _logger;
    protected int _processingTimeMs;
    protected int _randomDelayMaxMs;
    
    public string Id { get; }

    protected BaseProcessor(string id, ILogger logger)
    {
        Id = id;
        _logger = logger;
    }

    public void Configure(int processingTimeMs, int randomDelayMaxMs)
    {
        _processingTimeMs = processingTimeMs;
        _randomDelayMaxMs = randomDelayMaxMs;
    }
} 