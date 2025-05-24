namespace Presentation.Commands;

public class ShowStudentsCommand : ICommand
{
    private readonly Facade _facade;

    public ShowStudentsCommand(Facade facade)
    {
        _facade = facade;
    }

    public void Execute()
    {
        var students = _facade.GetDatabaseCore().GetAllStudents();
        
        Console.WriteLine("\nСписок всех студентов:");
        Console.WriteLine("ID\t\tИмя\t\tВозраст\t\tГруппа");
        foreach (var student in students)
        {
            Console.WriteLine($"{student.Id}\t\t{student.Name}\t\t{student.Age}\t\t{student.GroupId}");
        }
        Console.WriteLine();
    }
} 