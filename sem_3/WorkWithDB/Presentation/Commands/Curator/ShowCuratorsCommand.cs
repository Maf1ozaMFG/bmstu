namespace Presentation.Commands;

public class ShowCuratorsCommand : ICommand
{
    private readonly Facade _facade;

    public ShowCuratorsCommand(Facade facade)
    {
        _facade = facade;
    }

    public void Execute()
    {
        var curators = _facade.GetDatabaseCore().GetAllCurators();
        
        Console.WriteLine("\nСписок всех кураторов:");
        Console.WriteLine("ID\tИмя\tEmail\tГруппа");
        foreach (var curator in curators)
        {
            Console.WriteLine($"{curator.Id}\t{curator.Name}\t{curator.Email}\t{curator.GroupId}");
        }
        Console.WriteLine();
    }
} 