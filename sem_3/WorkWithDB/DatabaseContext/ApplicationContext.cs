using DatabaseModels;
using Microsoft.EntityFrameworkCore;
using System.Text.RegularExpressions;
using Group = DatabaseModels.Group;

namespace DatabaseContext;

public class ApplicationContext : DbContext
{
    private const string serverConfig = "Host=localhost;Port=5432;Database=university;Username=postgres;Password=1337";

    public ApplicationContext()
    {
        Database.EnsureCreated();
    }

    protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
    {
        optionsBuilder.UseNpgsql(serverConfig);
    }

    protected override void OnModelCreating(ModelBuilder modelBuilder)
    {
        // Конфигурация Student
        modelBuilder.Entity<Student>(entity =>
        {
            entity.HasKey(s => s.Id);
            entity.Property(s => s.Name).IsRequired();
            entity.Property(s => s.Age).IsRequired();
            entity.Property(s => s.GroupId).IsRequired();
            
            entity.HasOne(s => s.Group)
                .WithMany(g => g.Students)
                .HasForeignKey(s => s.GroupId)
                .OnDelete(DeleteBehavior.Cascade);
        });

        // Конфигурация Group
        modelBuilder.Entity<Group>(entity =>
        {
            entity.HasKey(g => g.Id);
            entity.Property(g => g.Name).IsRequired();
            entity.Property(g => g.CreationDate).IsRequired();
            entity.Property(g => g.CuratorId).IsRequired(false);

            entity.HasOne(g => g.Curator)
                .WithOne(c => c.Group)
                .HasForeignKey<Group>(g => g.CuratorId)
                .IsRequired(false);
        });

        // Конфигурация Curator
        modelBuilder.Entity<Curator>(entity =>
        {
            entity.HasKey(c => c.Id);
            entity.Property(c => c.Name).IsRequired();
            entity.Property(c => c.Email).IsRequired();
            entity.Property(c => c.GroupId).IsRequired(false);
        });

        base.OnModelCreating(modelBuilder);
    }

}

