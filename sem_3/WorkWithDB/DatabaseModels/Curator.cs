using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace DatabaseModels;

[Table("curators")]
public class Curator
{
    [Column("curator_id")]
    public int Id { get; set; }

    [Column("curator_name")]
    public string Name { get; set; } = null!;

    [Column("curator_email")]
    public string Email { get; set; } = null!;

    [Column("curator_group_id")]
    public int? GroupId { get; set; }

    [ForeignKey("GroupId")]
    public Group? Group { get; set; }
}

