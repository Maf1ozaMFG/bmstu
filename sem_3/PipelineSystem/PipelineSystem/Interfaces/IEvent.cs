namespace PipelineSystem.Interfaces;

public interface IEvent
{
    Guid Id { get; }
    DateTime CreatedAt { get; }
    string StudentId { get; }
    string CommitHash { get; }
    bool TestsPassed { get; set; }
} 