namespace PipelineSystem.Interfaces;

public interface IProcessor<T> where T : IEvent
{
    string Id { get; }
    void Configure(int processingTimeMs, int randomDelayMs);
} 