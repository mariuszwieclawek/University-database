#include "consoleGui.hpp"
#include "Windows.h"
#include "sstream"
#include <conio.h>
#include <cctype> 


ConsoleGUI::ConsoleGUI(StudentDatabase &  db) : m_db(db)
{
    auto action1 = [this]() { this->displayStudentsForSelectedFieldOfStudy(); };
    auto action2 = [this]() { this->m_db.displayStudents(); };
    auto action3 = [this]() { this->displayStudentsByLastname(); };
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
    std::cout << "hello" << std::endl;
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
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    m_db.displayStudentsByFieldOfStudy(fldOfStd);
}

void ConsoleGUI::displayStudentsByLastname(void)
{
    std::string lastname;
    std::cout << "Podaj nazwisko studenta ktorego chcesz wyszukac: ";
    std::cin >> lastname;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::vector<const Student*> students = m_db.findStudentsByLastname(lastname);

    if(students.empty() == true)
    {
        std::cout << "Nie udalo sie znalezc studentow" << std::endl;
    }
    else
    {
        std::cout << "Wyszukani studenci:" << std::endl;
        for(auto st : students)
        {
            st->showStudentEx();
            std::cout << std::endl << std::endl;
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
    std::cout << "Prosze wpisac:" << std::endl;
    std::cout << "Imie:";
    std::cin >> name;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Nazwisko:";
    std::cin >> lastname;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Adres:";
    std::getline(std::cin >> std::ws, address);
    std::cout << "Numer indeksu:";
    std::cin >> indexNumber;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Pesel:";
    std::cin >> pesel;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Plec:";
    std::cin >> gnr;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    m_db.addStudent(std::make_unique<MathStudent>(name, lastname, address, indexNumber, pesel, gnr));

    std::cout << "Dodano studenta!" << std::endl;
}

void ConsoleGUI::removeStudentByUser(void)
{
    std::string pesel;

    std::cout << "Podaj numer PESEL studenta ktorego chcesz usunac z bazy danych: ";
    std::cin >> pesel;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


    if(m_db.removeStudentByPesel(pesel) != true)
    {
        std::cout << "Zly numer PESEL! Nie udalo sie usunac" << std::endl;
    }
    else
    {
        std::cout << "Usunieto!" << std::endl;
    }
}

void ConsoleGUI::modifyStudentByUser(void)
{
    std::string pesel;
    std::cout << "Podaj PESEL studenta ktorego chcesz zmodyfikowac: ";
    std::cin >> pesel;

    bool isModified = m_db.modifyStudentByPesel(pesel);

    if(isModified == false)
    {
        std::cout << "Nie udalo sie znalezc studenta" << std::endl;
    }
    else
    {
        std::cout << "Udalo sie zmodyfikowac studenta!" << std::endl;
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

    char choice_ch;
    int choice_digit;
    MenuItem currentMenu = m_mainMenu;
    std::stack<MenuItem> menuStack;
    menuStack.push(currentMenu);
    m_isMenuEnabled = true;

    system("cls");

    
    while (m_isMenuEnabled) 
    {
        displayMenu(currentMenu);
        choice_ch = _getch();
        if (isdigit(choice_ch)) 
        { 
            choice_digit = choice_ch - '0'; // convert to digit
        } 
        else 
        {
            std::cout << "Invalid input. Please press a digit key (0-9)." << std::endl;
            break;
        }
        system("cls");

        /* Check input parameter */
        if (choice_digit < 0  || choice_digit > currentMenu.subMenu.size()) 
        {
            continue;
        }

        /* Menu stack handle */
        if (choice_digit == 0 && !menuStack.empty())
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
        if( choice_digit != 0)
        {
            MenuItem selectedOption = currentMenu.subMenu[choice_digit - 1];
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
                    exitFromSelectedAction();
                }
            } 
        }
    }
}

void ConsoleGUI::exitFromSelectedAction()
{
    std::string input;
    char choice_ch;
    int choice_digit;

    std::cout << "===========================================================================================" << std::endl;
    std::cout << "Wcisnij '0' aby wyjsc: " << std::endl;
    while (true) 
    {
        choice_ch = _getch();
        if (isdigit(choice_ch)) 
        { 
            choice_digit = choice_ch - '0'; // convert to digit
        } 

        if(choice_digit == 0)
        {
            system("cls");
            break;
        }
    }
}