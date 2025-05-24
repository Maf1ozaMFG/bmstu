using PipelineSystem.Interfaces;

namespace PipelineSystem.Infrastructure;

using System;
using System.IO;
using System.Threading.Tasks;

public class Logger : ILogger
{
    private readonly string _logPath;
    private readonly string _statsPath;
    private readonly object _logLock = new();
    private readonly object _statsLock = new();
    private readonly object _consoleLock = new();

    public Logger(string logPath, string statsPath)
    {
        _logPath = logPath;
        _statsPath = statsPath;
    }

    public void LogEvent(string message)
    {
        var logMessage = $"{DateTime.Now:yyyy-MM-dd HH:mm:ss.fff} - {message}";
        lock (_logLock)
        {
            File.AppendAllText(_logPath, logMessage + Environment.NewLine);
            Console.WriteLine($"{DateTime.Now:yyyy-MM-dd HH:mm:ss.fff} - {message}");
        }
    }


    public void LogStatistics(string statistics)
    {
        lock (_statsLock)
        {
            File.AppendAllText(_statsPath, statistics + Environment.NewLine);
            Console.WriteLine(statistics);
        }
    }

    public async Task LogStatisticsAsync(string statistics)
    {
        await File.AppendAllTextAsync(_statsPath, statistics + Environment.NewLine);
    }
}