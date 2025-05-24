namespace Presentation.Commands;

public class ShowGroupCommand : ICommand
{
    private readonly Facade _facade;

    public ShowGroupCommand(Facade facade)
    {
        _facade = facade;
    }

    public void Execute()
    {
        Console.WriteLine("Введите ID группы:");
        if (!int.TryParse(Console.ReadLine(), out var id))
        {
            throw new Exception("Некорректный ID");
        }

        var group = _facade.GetDatabaseCore().GetGroupById(id);
        Console.WriteLine("\nИнформация о группе:");
        Console.WriteLine($"ID: {group.Id}");
        Console.WriteLine($"Название: {group.Name}");
        Console.WriteLine($"Дата создания: {group.CreationDate:d}");
        Console.WriteLine($"ID куратора: {group.CuratorId}");
        Console.WriteLine();
    }
} 