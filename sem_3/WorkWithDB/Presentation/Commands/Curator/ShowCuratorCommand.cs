namespace Presentation.Commands;

public class ShowCuratorCommand : ICommand
{
    private readonly Facade _facade;

    public ShowCuratorCommand(Facade facade)
    {
        _facade = facade;
    }

    public void Execute()
    {
        Console.WriteLine("Введите ID куратора:");
        if (!int.TryParse(Console.ReadLine(), out var id))
        {
            throw new Exception("Некорректный ID");
        }

        var curator = _facade.GetDatabaseCore().GetCuratorById(id);
        Console.WriteLine("\nИнформация о кураторе:");
        Console.WriteLine($"ID: {curator.Id}");
        Console.WriteLine($"Имя: {curator.Name}");
        Console.WriteLine($"Email: {curator.Email}");
        Console.WriteLine($"ID группы: {curator.GroupId}");
        Console.WriteLine();
    }
} 