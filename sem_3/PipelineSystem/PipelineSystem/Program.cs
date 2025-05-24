namespace PipelineSystem;

using System;
using System.IO;
using PipelineSystem.Services;
using PipelineSystem.Infrastructure;
using System.Text.Json;

class Program
{
    static void Main(string[] args)
    {
        var logPath = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "pipeline.log");
        var statsPath = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "statistics.log");

        File.WriteAllText(logPath, string.Empty);
        File.WriteAllText(statsPath, string.Empty);

        var config = JsonSerializer.Deserialize<Models.PipelineConfig>(
            File.ReadAllText("config.json"),
            new JsonSerializerOptions 
            { 
                PropertyNameCaseInsensitive = true 
            }
        );

        var logger = new Logger(logPath, statsPath);
        var cts = new CancellationTokenSource();

        Console.CancelKeyPress += (s, e) =>
        {
            e.Cancel = true;
            cts.Cancel();
        };

        Console.WriteLine("\nНажмите Ctrl+C для завершения...");
        using var coordinator = new PipelineCoordinator(config!, logger);
        coordinator.Start();

        try
        { 
            while (!cts.Token.IsCancellationRequested)
            {
                Thread.Sleep(100);
            }
        }
        finally
        {
            coordinator.Dispose();
        }
    }
}
