namespace Presentation.Commands;

public class AssignCuratorToGroupCommand : ICommand
{
    private readonly Facade _facade;

    public AssignCuratorToGroupCommand(Facade facade)
    {
        _facade = facade;
    }

    public void Execute()
    {
        Console.WriteLine("Введите ID куратора:");
        if (!int.TryParse(Console.ReadLine(), out var curatorId))
        {
            throw new Exception("Некорректный ID куратора");
        }

        Console.WriteLine("Введите ID группы:");
        if (!int.TryParse(Console.ReadLine(), out var groupId))
        {
            throw new Exception("Некорректный ID группы");
        }

        _facade.GetDatabaseCore().AssignCuratorToGroup(curatorId, groupId);
        Console.WriteLine("Куратор успешно назначен группе");
    }
} 