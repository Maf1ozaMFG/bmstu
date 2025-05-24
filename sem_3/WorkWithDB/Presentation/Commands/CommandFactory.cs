using System.Collections.ObjectModel;

namespace Presentation.Commands;

public class CommandFactory : ICommandFactory
{
    private readonly Facade _facade;
    private readonly Dictionary<string, Func<ICommand>> _commandMap;

    public CommandFactory(Facade facade)
    {
        _facade = facade;
        _commandMap = new Dictionary<string, Func<ICommand>>
        {
            // Команды для студентов
            { "create_student", () => new CreateStudentCommand(_facade) },
            { "update_student", () => new UpdateStudentCommand(_facade) },
            { "delete_student", () => new DeleteStudentCommand(_facade) },
            { "show_students", () => new ShowStudentsCommand(_facade) },
            { "show_student", () => new ShowStudentCommand(_facade) },
            { "count_students", () => new CountStudentsInGroupCommand(_facade) },
            { "average_age", () => new AverageAgeInGroupCommand(_facade) },

            // Команды для групп
            { "create_group", () => new CreateGroupCommand(_facade) },
            { "update_group", () => new UpdateGroupCommand(_facade) },
            { "delete_group", () => new DeleteGroupCommand(_facade) },
            { "show_groups", () => new ShowGroupsCommand(_facade) },
            { "show_group", () => new ShowGroupCommand(_facade) },

            // Команды для кураторов
            { "create_curator", () => new CreateCuratorCommand(_facade) },
            { "update_curator", () => new UpdateCuratorCommand(_facade) },
            { "delete_curator", () => new DeleteCuratorCommand(_facade) },
            { "show_curators", () => new ShowCuratorsCommand(_facade) },
            { "show_curator", () => new ShowCuratorCommand(_facade) },
            { "assign_curator", () => new AssignCuratorToGroupCommand(_facade) },
            { "get_curator_by_student", () => new GetCuratorByStudentCommand(_facade) }
        };
    }

    public ICommand CreateCommand(string commandType)
    {
        if (_commandMap.TryGetValue(commandType, out var factory))
        {
            return factory();
        }
        throw new ArgumentException($"Unknown command type: {commandType}");
    }

    public IReadOnlyDictionary<string, Func<ICommand>> GetCommandMap()
    {
        return new ReadOnlyDictionary<string, Func<ICommand>>(_commandMap);
    }
} 