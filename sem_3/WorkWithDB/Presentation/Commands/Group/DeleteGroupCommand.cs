namespace Presentation.Commands;

public class DeleteGroupCommand : ICommand
{
    private readonly Facade _facade;

    public DeleteGroupCommand(Facade facade)
    {
        _facade = facade;
    }

    public void Execute()
    {
        Console.WriteLine("Введите ID группы для удаления:");
        if (!int.TryParse(Console.ReadLine(), out var id))
        {
            throw new Exception("Некорректный ID");
        }

        _facade.GetDatabaseCore().DeleteGroupById(id);
        Console.WriteLine("Группа успешно удалена");
    }
} 