namespace Presentation.Commands;

public class CountStudentsInGroupCommand : ICommand
{
    private readonly Facade _facade;

    public CountStudentsInGroupCommand(Facade facade)
    {
        _facade = facade;
    }

    public void Execute()
    {
        Console.WriteLine("Введите ID группы:");
        if (!int.TryParse(Console.ReadLine(), out var groupId))
        {
            throw new Exception("Некорректный ID группы");
        }

        var count = _facade.GetDatabaseCore().GetStudentsCountInGroup(groupId);
        Console.WriteLine($"\nКоличество студентов в группе: {count}");
    }
} 