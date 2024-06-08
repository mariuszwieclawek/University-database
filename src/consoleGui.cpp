#include "consoleGui.hpp"



ConsoleGUI::ConsoleGUI(StudentDatabase &  db) : m_db(db)
{
    auto action1 = [this]() { this->action1(); };
    auto action2 = [this]() { this->m_db.displayStudents(); };
    auto action3 = [this]() { this->addStudentByUser(); };
    auto action4 = [this]() { this->removeStudentByUser(); };

    m_mainMenu =
    {
        "Menu glowne", action1,
        {
            {"Lista kierunkow na uczelni", nullptr, 
            {
                {"Podopcja 1", action1, {}},
                {"Podopcja 2", action1, {}}
            }},
            {"Lista studentow na uczelni", action2, {}},
            {"Dodaj studenta", action3, {}},
            {"Usun studenta", action4, {}}
        }
    };
};

void ConsoleGUI::action1(void)
{
    std::cout << "hello\n";
}

void ConsoleGUI::removeStudentByUser(void)
{
    std::string pesel;

    std::cout << "Podaj numer PESEL studenta ktorego chcesz usunac z bazy danych: ";
    std::cin >> pesel;

    if(m_db.removeStudentByPesel(pesel) != true)
    {
        std::cout << "Zly numer PESEL! Nie udalo sie usunac" << std::endl;
    }
    else
    {
        std::cout << "Usunieto!" << std::endl;
        m_db.saveAllStudentsToCSV();
    }
}

void ConsoleGUI::addStudentByUser(void)
{
    std::string name;
    std::string lastname;
    std::string address;
    int indexNumber; 
    std::string pesel; 
    Gender gnr;
    std::cout << "Prosze wpisac:\nImie:";
    std::cin >> name;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Nazwisko:";
    std::cin >> lastname;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Adres:";
    std::getline(std::cin >> std::ws, address);
    std::cout << "Numer indeksu:";
    std::cin >> indexNumber;
    std::cout << "Pesel:";
    std::cin >> pesel;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Plec:";
    std::cin >> gnr;

    m_db.addStudent(std::make_unique<MathStudent>(name, lastname, address, indexNumber, pesel, gnr));

    std::cout << "Dodano studenta!\n";
}

void ConsoleGUI::displayMenu(const MenuItem & selectedMenu) 
{
    std::cout << "===========================================================================================" << std::endl;
    for (int i = 0; i < selectedMenu.subMenu.size(); i++) 
    {
        std::cout << i+1 << ". " << selectedMenu.subMenu[i].label << std::endl;
    }
    std::cout << "0. Wyjscie " << std::endl;
    std::cout << "===========================================================================================" << std::endl;
    std::cout << "Wybierz opcje: ";
}

void ConsoleGUI::run() 
{
    if(m_mainMenu.label.empty())
    {
        std::cout << "[ERROR] Zdefiniuj menu w konstruktorze ConsoleGUI!";
        return;
    }

    unsigned int choice;
    MenuItem currentMenu = m_mainMenu;
    std::stack<MenuItem> menuStack;
    menuStack.push(currentMenu);
    m_isMenuEnabled = true;

    while (m_isMenuEnabled) 
    {
        system("cls");

        displayMenu(currentMenu);
        std::cin >> choice;

        /* Check input parameter */
        if (choice < 0  || choice > currentMenu.subMenu.size()) 
        {
            continue;
        }

        /* Menu stack handle */
        if (choice == 0 && !menuStack.empty())
        {
            menuStack.pop();
            if(!menuStack.empty())
            {
                currentMenu = menuStack.top();
            }
            else
            {
                m_isMenuEnabled = false;
            }
        }

        /* Run selected submenu */
        if( choice != 0)
        {
            MenuItem selectedOption = currentMenu.subMenu[choice - 1];
            if (!selectedOption.subMenu.empty())
            {
                currentMenu = selectedOption;
                menuStack.push(currentMenu);
            }

            if (selectedOption.action != nullptr)
            {
                performSelectedAction(selectedOption.action);
            }
        }

    }
}

void ConsoleGUI::performSelectedAction(std::function<void()> action)
{
    unsigned int choice;
    while(true)
        {
            system("cls");
            action();
            std::cout << "===========================================================================================" << std::endl;
            std::cout << "Wpisz '0' aby wyjsc: ";
            std::cin >> choice;
            if(choice == 0)
            {
                break;
            }
        }
}