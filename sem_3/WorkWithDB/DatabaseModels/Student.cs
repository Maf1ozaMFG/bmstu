using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace DatabaseModels;

[Table("students")]
public class Student
{
    [Column("student_id")]
    public int Id { get; set; }

    [Column("student_group_id")]
    public int GroupId { get; set; }
    public Group? Group { get; set; }

    [Column("student_name")]
    public string Name { get; set; } = null!;

    [Column("student_age")]
    public int Age { get; set; }
}
