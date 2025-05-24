namespace PipelineSystem.Models;

using PipelineSystem.Interfaces;
using PipelineSystem.Services;

public class CommitEvent : IEvent
{
    public Guid Id { get; set; }
    public string StudentId { get; set; }
    public string CommitHash { get; set; }
    public bool TestsPassed { get; set; }
    public bool NeedsRevision { get; set; }
    public DateTime CreatedAt { get; set; }

    public CommitEvent(string studentId, string commitHash)
    {
        Id = Guid.NewGuid();
        StudentId = studentId;
        CommitHash = commitHash;
        TestsPassed = false;
        NeedsRevision = false;
        CreatedAt = DateTime.UtcNow;
    }
} 