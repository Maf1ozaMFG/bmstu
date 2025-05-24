using Core;
using Presentation.Commands;

namespace Presentation;

public class Facade
{
    private readonly DatabaseCore _databaseCore;

    public Facade(DatabaseCore databaseCore)
    {
        _databaseCore = databaseCore;
    }

    public void Execute(ICommand command)
    {
        command.Execute();
    }

    public DatabaseCore GetDatabaseCore() => _databaseCore;
} 