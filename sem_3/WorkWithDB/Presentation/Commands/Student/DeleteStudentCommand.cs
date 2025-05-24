namespace Presentation.Commands;

public class DeleteStudentCommand : ICommand
{
    private readonly Facade _facade;

    public DeleteStudentCommand(Facade facade)
    {
        _facade = facade;
    }

    public void Execute()
    {
        Console.WriteLine("Введите ID студента для удаления:");
        if (!int.TryParse(Console.ReadLine(), out var id))
        {
            throw new Exception("Некорректный ID");
        }

        _facade.GetDatabaseCore().DeleteStudentById(id);
        Console.WriteLine("Студент успешно удален");
    }
} 