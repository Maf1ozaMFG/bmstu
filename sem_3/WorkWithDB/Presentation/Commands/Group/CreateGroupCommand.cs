namespace Presentation.Commands;

public class CreateGroupCommand : ICommand
{
    private readonly Facade _facade;

    public CreateGroupCommand(Facade facade)
    {
        _facade = facade;
    }

    public void Execute()
    {
        Console.WriteLine("Введите название группы:");
        var name = Console.ReadLine() ?? throw new Exception("Название не может быть пустым");

        _facade.GetDatabaseCore().CreateGroup(name);
        Console.WriteLine("Группа успешно создана");
    }
} 