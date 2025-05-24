using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace DatabaseModels;

[Table("groups")]
public class Group
{
    [Column("group_id")]
    public int Id { get; set; }

    [Column("group_name")]
    public string Name { get; set; } = null!;

    [Column("group_creation_date")]
    public DateTime CreationDate { get; set; }

    [Column("curator_id")]
    public int? CuratorId { get; set; }

    [ForeignKey("CuratorId")]
    public Curator? Curator { get; set; }

    public ICollection<Student> Students { get; set; } = new List<Student>();
}

