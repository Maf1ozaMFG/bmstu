namespace PipelineSystem.Interfaces;

public interface ILogger
{
    void LogEvent(string message);
    void LogStatistics(string statistics);
    Task LogStatisticsAsync(string statistics);
} 