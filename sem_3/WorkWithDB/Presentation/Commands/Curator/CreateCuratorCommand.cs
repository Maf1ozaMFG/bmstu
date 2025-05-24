namespace Presentation.Commands;

public class CreateCuratorCommand : ICommand
{
    private readonly Facade _facade;

    public CreateCuratorCommand(Facade facade)
    {
        _facade = facade;
    }

    public void Execute()
    {
        Console.WriteLine("Введите имя куратора:");
        var name = Console.ReadLine() ?? throw new Exception("Имя не может быть пустым");

        Console.WriteLine("Введите email куратора:");
        var email = Console.ReadLine() ?? throw new Exception("Email не может быть пустым");

        _facade.GetDatabaseCore().CreateCurator(name, email);
        Console.WriteLine("Куратор успешно создан");
    }
} 