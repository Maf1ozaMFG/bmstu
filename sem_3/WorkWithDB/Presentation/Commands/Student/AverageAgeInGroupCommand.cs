namespace Presentation.Commands;

public class AverageAgeInGroupCommand : ICommand
{
    private readonly Facade _facade;

    public AverageAgeInGroupCommand(Facade facade)
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

        var averageAge = _facade.GetDatabaseCore().GetAverageAgeInGroup(groupId);
        Console.WriteLine($"\nСредний возраст студентов в группе: {averageAge:F2}");
    }
} 