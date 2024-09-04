#include "consoleGui.hpp"



ConsoleGUI::ConsoleGUI(StudentDatabase &  db) : m_db(db)
{
    auto action1 = [this]() { this->displayStudentsForSelectedFieldOfStudy(); };
    auto action2 = [this]() { this->m_db.displayStudents(); };
    auto action3 = [this]() { this->findStudentByLastname(); };
    auto action4 = [this]() { this->addStudentByUser(); };
    auto action5 = [this]() { this->removeStudentByUser(); };
    auto action6 = [this]() { this->modifyStudentByUser(); };
    auto action7 = [this]() { this->displayFieldsOfStudy(); };

    m_mainMenu =
    {
        "Menu glowne", nullptr,
        {
            {"Lista kierunkow na uczelni", action7, 
            {
                {"Wyswietl liste studentow wybranego kierunku", action1, {}},
                {"Podopcja 2", action2, {}}
            }},
            {"Lista studentow na uczelni", action2, {}},
            {"Wyszukaj studenta", action3, {}},
            {"Dodaj studenta", action4, {}},
            {"Usun studenta", action5, {}},
            {"Modyfikuj studenta", action6, {}}
        }
    };
};

void ConsoleGUI::action1(void)
{
    std::cout << "hello\n";
}

void ConsoleGUI::displayFieldsOfStudy(void) const
{
    std::set<std::string> fields_of_study = m_db.getFieldsOfStudy();
    for(auto fld_of_st : fields_of_study)
    {
        std::cout << fld_of_st << std::endl;
    }
}

void ConsoleGUI::displayStudentsForSelectedFieldOfStudy(void) const
{
    std::string fldOfStd;
    std::cout << "Please enter field of study: ";
    std::cin >> fldOfStd;
    m_db.displayStudentsByFieldOfStudy(fldOfStd);
}

void ConsoleGUI::findStudentByLastname(void)
{
    std::string lastname;
    std::cout << "Podaj nazwisko studenta ktorego chcesz wyszukac: ";
    std::cin >> lastname;

    std::vector<Student*> students = m_db.findStudentByLastname(lastname);

    if(students.empty() == true)
    {
        std::cout << "Nie udalo sie znalezc studenta/ow" << std::endl;
    }
    else
    {
        std::cout << "Wyszukany/i student/ci:" << std::endl;
        for(auto st : students)
        {
            st->showStudentEx();
            std::cout << "\n\n";
        }
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

void ConsoleGUI::modifyStudentByUser(void)
{
    std::string pesel;
    std::cout << "Podaj PESEL studenta ktorego chcesz zmodyfikowac: ";
    std::cin >> pesel;

    Student* stdnt = m_db.findStudentByPesel(pesel);

    if(stdnt == nullptr)
    {
        std::cout << "Nie udalo sie znalezc studenta" << std::endl;
    }
    else
    {
        std::cout << "Udalo sie znalezc studenta. Aktualne dane:\n" << std::endl;
        stdnt->showStudentEx();
        stdnt->modifyStudent();
        m_db.saveAllStudentsToCSV();
        std::cout << "\nUdalo sie zmodyfikowac studenta!" << std::endl;
    }
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

    system("cls");

    while (m_isMenuEnabled) 
    {
        displayMenu(currentMenu);
        std::cin >> choice;
        system("cls");

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
                selectedOption.action();
                if (selectedOption.subMenu.empty())
                {
                    exitFromSelectedAction(selectedOption.action);
                }
            } 
        }

    }
}

void ConsoleGUI::exitFromSelectedAction(std::function<void()> action)
{
    unsigned int choice;
    while(true)
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "===========================================================================================" << std::endl;
            std::cout << "Wpisz '0' aby wyjsc: ";
            std::cin >> choice;
            if(choice == 0)
            {
                system("cls");
                break;
            }
            system("cls");
            action();
        }
}