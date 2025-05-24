namespace Presentation.Commands;

public class UpdateCuratorCommand : ICommand
{
    private readonly Facade _facade;

    public UpdateCuratorCommand(Facade facade)
    {
        _facade = facade;
    }

    public void Execute()
    {
        Console.WriteLine("Введите ID куратора для обновления:");
        if (!int.TryParse(Console.ReadLine(), out var id))
        {
            throw new Exception("Некорректный ID");
        }

        Console.WriteLine("Введите новое имя куратора:");
        var name = Console.ReadLine() ?? throw new Exception("Имя не может быть пустым");

        _facade.GetDatabaseCore().UpdateCuratorNameById(id, name);
        Console.WriteLine("Информация о кураторе успешно обновлена");
    }
} 