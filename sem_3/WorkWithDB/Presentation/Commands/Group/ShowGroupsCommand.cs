namespace Presentation.Commands;

public class ShowGroupsCommand : ICommand
{
    private readonly Facade _facade;

    public ShowGroupsCommand(Facade facade)
    {
        _facade = facade;
    }

    public void Execute()
    {
        var groups = _facade.GetDatabaseCore().GetAllGroups();
        
        Console.WriteLine("\nСписок всех групп:");
        Console.WriteLine("ID\t\tНазвание\t\tДата создания\t\tКуратор");
        foreach (var group in groups)
        {
            Console.WriteLine($"{group.Id}\t\t{group.Name}\t\t{group.CreationDate}\t\t{group.CuratorId}");
        }
        Console.WriteLine();
    }
} 