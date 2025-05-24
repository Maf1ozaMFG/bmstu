namespace Presentation.Commands;

public class ShowStudentCommand : ICommand
{
    private readonly Facade _facade;

    public ShowStudentCommand(Facade facade)
    {
        _facade = facade;
    }

    public void Execute()
    {
        Console.WriteLine("Введите ID студента:");
        if (!int.TryParse(Console.ReadLine(), out var id))
        {
            throw new Exception("Некорректный ID");
        }

        var student = _facade.GetDatabaseCore().GetStudentById(id);
        Console.WriteLine("\nИнформация о студенте:");
        Console.WriteLine($"ID: {student.Id}");
        Console.WriteLine($"Имя: {student.Name}");
        Console.WriteLine($"Возраст: {student.Age}");
        Console.WriteLine($"Группа: {student.GroupId}");
        Console.WriteLine();
    }
} 