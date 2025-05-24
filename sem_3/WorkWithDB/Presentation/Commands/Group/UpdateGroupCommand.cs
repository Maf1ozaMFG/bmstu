namespace Presentation.Commands;

public class UpdateGroupCommand : ICommand
{
    private readonly Facade _facade;

    public UpdateGroupCommand(Facade facade)
    {
        _facade = facade;
    }

    public void Execute()
    {
        Console.WriteLine("Введите ID группы для обновления:");
        if (!int.TryParse(Console.ReadLine(), out var id))
        {
            throw new Exception("Некорректный ID");
        }

        Console.WriteLine("Введите новое название группы:");
        var name = Console.ReadLine() ?? throw new Exception("Название не может быть пустым");

        Console.WriteLine("Введите новую дату создания (в формате дд.мм.гггг):");
        if (!DateTime.TryParse(Console.ReadLine(), out var creationDate))
        {
            throw new Exception("Некорректная дата");
        }

        _facade.GetDatabaseCore().UpdateGroupNameById(id, name);
        _facade.GetDatabaseCore().UpdateGroupCreationDateById(id, creationDate);
        Console.WriteLine("Информация о группе успешно обновлена");
    }
} 