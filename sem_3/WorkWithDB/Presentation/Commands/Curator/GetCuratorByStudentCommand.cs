namespace Presentation.Commands;

public class GetCuratorByStudentCommand : ICommand
{
    private readonly Facade _facade;

    public GetCuratorByStudentCommand(Facade facade)
    {
        _facade = facade;
    }

    public void Execute()
    {
        Console.WriteLine("Введите ID студента:");
        if (!int.TryParse(Console.ReadLine(), out var studentId))
        {
            throw new Exception("Некорректный ID студента");
        }

        var curatorName = _facade.GetDatabaseCore().GetCuratorNameByStudentId(studentId);
        Console.WriteLine($"\nКуратор студента: {curatorName}");
    }
} 