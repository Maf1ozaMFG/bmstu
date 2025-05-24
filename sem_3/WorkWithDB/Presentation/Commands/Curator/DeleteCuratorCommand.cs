namespace Presentation.Commands;

public class DeleteCuratorCommand : ICommand
{
    private readonly Facade _facade;

    public DeleteCuratorCommand(Facade facade)
    {
        _facade = facade;
    }

    public void Execute()
    {
        Console.WriteLine("Введите ID куратора для удаления:");
        if (!int.TryParse(Console.ReadLine(), out var id))
        {
            throw new Exception("Некорректный ID");
        }

        _facade.GetDatabaseCore().DeleteCuratorById(id);
        Console.WriteLine("Куратор успешно удален");
    }
} 