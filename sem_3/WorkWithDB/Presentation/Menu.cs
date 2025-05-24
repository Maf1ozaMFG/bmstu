using Presentation.Commands;

namespace Presentation;

public class Menu
{
    private readonly Facade _facade;
    private readonly CommandFactory _commandFactory;
    private readonly Dictionary<string, string> _menuItems;

    public Menu(Facade facade)
    {
        _facade = facade;
        _commandFactory = new CommandFactory(facade);
        _menuItems = new Dictionary<string, string>
        {
            // Меню студентов
            { "1.1", "create_student" },
            { "1.2", "show_students" },
            { "1.3", "show_student" },
            { "1.4", "update_student" },
            { "1.5", "delete_student" },
            { "1.6", "count_students" },
            { "1.7", "average_age" },

            // Меню групп
            { "2.1", "create_group" },
            { "2.2", "show_groups" },
            { "2.3", "show_group" },
            { "2.4", "update_group" },
            { "2.5", "delete_group" },

            // Меню кураторов
            { "3.1", "create_curator" },
            { "3.2", "show_curators" },
            { "3.3", "show_curator" },
            { "3.4", "update_curator" },
            { "3.5", "delete_curator" },
            { "3.6", "assign_curator" },
            { "3.7", "get_curator_by_student" }
        };
    }

    public void ShowMainMenu()
    {
        while (true)
        {
            Console.WriteLine("\nГлавное меню:");
            Console.WriteLine("1. Управление студентами");
            Console.WriteLine("2. Управление группами");
            Console.WriteLine("3. Управление кураторами");
            Console.WriteLine("0. Выход");

            Console.Write("\nВыберите пункт меню: ");
            var choice = Console.ReadLine();

            if (choice == "0")
                break;

            switch (choice)
            {
                case "1":
                    ShowStudentMenu();
                    break;
                case "2":
                    ShowGroupMenu();
                    break;
                case "3":
                    ShowCuratorMenu();
                    break;
                default:
                    Console.WriteLine("Некорректный выбор");
                    break;
            }
        }
    }

    private void ShowStudentMenu()
    {
        Console.WriteLine("\nУправление студентами:");
        Console.WriteLine("1. Создать студента");
        Console.WriteLine("2. Показать всех студентов");
        Console.WriteLine("3. Показать студента по ID");
        Console.WriteLine("4. Обновить данные студента");
        Console.WriteLine("5. Удалить студента");
        Console.WriteLine("6. Показать количество студентов в группе");
        Console.WriteLine("7. Показать средний возраст в группе");
        Console.WriteLine("0. Назад");

        Console.Write("\nВыберите пункт меню: ");
        var choice = Console.ReadLine();

        if (choice == "0")
            return;

        var menuKey = $"1.{choice}";
        ExecuteCommand(menuKey);
    }

    private void ShowGroupMenu()
    {
        Console.WriteLine("\nУправление группами:");
        Console.WriteLine("1. Создать группу");
        Console.WriteLine("2. Показать все группы");
        Console.WriteLine("3. Показать группу по ID");
        Console.WriteLine("4. Обновить данные группы");
        Console.WriteLine("5. Удалить группу");
        Console.WriteLine("0. Назад");

        Console.Write("\nВыберите пункт меню: ");
        var choice = Console.ReadLine();

        if (choice == "0")
            return;

        var menuKey = $"2.{choice}";
        ExecuteCommand(menuKey);
    }

    private void ShowCuratorMenu()
    {
        Console.WriteLine("\nУправление кураторами:");
        Console.WriteLine("1. Создать куратора");
        Console.WriteLine("2. Показать всех кураторов");
        Console.WriteLine("3. Показать куратора по ID");
        Console.WriteLine("4. Обновить данные куратора");
        Console.WriteLine("5. Удалить куратора");
        Console.WriteLine("6. Назначить куратора группе");
        Console.WriteLine("7. Найти куратора по ID студента");
        Console.WriteLine("0. Назад");

        Console.Write("\nВыберите пункт меню: ");
        var choice = Console.ReadLine();

        if (choice == "0")
            return;

        var menuKey = $"3.{choice}";
        ExecuteCommand(menuKey);
    }

    private void ExecuteCommand(string menuKey)
    {
        try
        {
            if (_menuItems.TryGetValue(menuKey, out var commandType))
            {
                var command = _commandFactory.CreateCommand(commandType);
                _facade.Execute(command);
            }
            else
            {
                Console.WriteLine("Некорректный выбор");
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка: {ex.Message}");
        }
    }
} 