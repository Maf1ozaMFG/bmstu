namespace Presentation.Commands;

public interface ICommandFactory
{
    ICommand CreateCommand(string commandType);
} 