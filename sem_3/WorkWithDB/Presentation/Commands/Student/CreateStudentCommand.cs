namespace Presentation.Commands;

public class CreateStudentCommand : ICommand
{
    private readonly Facade _facade;

    public CreateStudentCommand(Facade facade)
    {
        _facade = facade;
    }

    public void Execute()
    {
        Console.WriteLine("Введите имя студента:");
        var name = Console.ReadLine() ?? throw new Exception("Имя не может быть пустым");

        Console.WriteLine("Введите возраст студента:");
        if (!int.TryParse(Console.ReadLine(), out var age))
        {
            throw new Exception("Некорректный возраст");
        }

        Console.WriteLine("Введите ID группы:");
        if (!int.TryParse(Console.ReadLine(), out var groupId))
        {
            throw new Exception("Некорректный ID группы");
        }

        _facade.GetDatabaseCore().CreateStudent(name, age, groupId);
        Console.WriteLine("Студент успешно создан");
    }
} 