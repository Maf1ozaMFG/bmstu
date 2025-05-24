using Core;
using DatabaseContext;

namespace Presentation;

public class Program
{
    public static void Main()
    {
        using (ApplicationContext db = new ApplicationContext())
        {
            var databaseCore = new DatabaseCore(db);
            var facade = new Facade(databaseCore);
            var menu = new Menu(facade);

            menu.ShowMainMenu();
        }
    }
}
