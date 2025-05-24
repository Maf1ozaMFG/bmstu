namespace Presentation.Commands;

public class UpdateStudentCommand : ICommand
{
    private readonly Facade _facade;

    public UpdateStudentCommand(Facade facade)
    {
        _facade = facade;
    }

    public void Execute()
    {
        Console.WriteLine("Введите ID студента для обновления:");
        if (!int.TryParse(Console.ReadLine(), out var id))
        {
            throw new Exception("Некорректный ID");
        }

        Console.WriteLine("Введите новое имя студента:");
        var name = Console.ReadLine() ?? throw new Exception("Имя не может быть пустым");

        Console.WriteLine("Введите новый возраст студента:");
        if (!int.TryParse(Console.ReadLine(), out var age))
        {
            throw new Exception("Некорректный возраст");
        }

        Console.WriteLine("Введите новый ID группы:");
        if (!int.TryParse(Console.ReadLine(), out var groupId))
        {
            throw new Exception("Некорректный ID группы");
        }

        _facade.GetDatabaseCore().UpdateStudent(id, name, age, groupId);
        Console.WriteLine("Информация о студенте успешно обновлена");
    }
} 