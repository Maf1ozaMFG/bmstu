namespace PipelineSystem.Models;

public class PipelineConfig
{
    public int NumberOfStudents { get; set; }
    public int NumberOfTesters { get; set; }
    public int NumberOfTeachers { get; set; }
    public int StudentEmitFrequencyMs { get; set; }
    public int RandomDelayMaxMs { get; set; }
    public int TestProcessingTimeMs { get; set; }
    public int TeacherProcessingTimeMs { get; set; }
    public int ProcessingRandomDelayMs { get; set; }
} 