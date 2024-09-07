#include "consoleGui.hpp"
#include "Windows.h"
#include "sstream"
#include <conio.h>
#include <cctype> 


ConsoleGUI::ConsoleGUI(StudentDatabase &  db) : m_db(db)
{
    auto action1 = [this]() { this->displayFieldsOfStudy(); };
    auto action2 = [this]() { this->displayStudentsForSelectedFieldOfStudy(); };
    auto action3 = [this]() { this->action1(); };
    auto action4 = [this]() { this->m_db.displayStudents(); };
    auto action5 = [this]() { this->displayStudentsByLastname(); };
    auto action6 = [this]() { this->addStudentByUser(); };
    auto action7 = [this]() { this->removeStudentByUser(); };
    auto action8 = [this]() { this->modifyStudentByUser(); };
    auto action9 = [this]() { this->sortStudentsByLastNameAtoZ(); };
    auto action10 = [this]() { this->sortStudentsByLastNameZtoA(); };
    auto action11 = [this]() { this->sortStudentsByIndexAscending(); };
    auto action12 = [this]() { this->sortStudentsByIndexDescending(); };

    m_mainMenu =
    {
        "Main Menu", nullptr,
        {
            {"Fields of study list", action1, 
            {
                {"Student list for selected field of study", action2, {}},
                {"TO DO", action3, {}}
            }},
            {"Student list", action4, {}},
            {"Sort student list", nullptr, 
            {
                {"Sort students by lastname A to Z", action9, {}},
                {"Sort students by lastname Z to A", action10, {}},
                {"Sort students by index number ascending", action11, {}},
                {"Sort students by index number descending", action12, {}},
            }},
            {"Search for student", action5, {}},
            {"Add student", action6, {}},
            {"Remove student", action7, {}},
            {"Modify student", action8, {}}
        }
    };
};

void ConsoleGUI::action1(void)
{
    std::cout << "hello" << std::endl;
}

void ConsoleGUI::displayFieldsOfStudy(void) const
{
    std::cout << "List of fields of study at the university:" << std::endl;
    std::set<std::string> fields_of_study = m_db.getFieldsOfStudy();
    int no = 0;
    for(auto fld_of_st : fields_of_study)
    {
        std::cout << "\t" << no << "." << fld_of_st << std::endl;
    }
    std::cout << std::endl;
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

void ConsoleGUI::displayStudentsByLastname(void) const
{
    m_db.displayStudents();
    std::cout << "===========================================================================================" << std::endl << std::endl;
    std::string lastname;
    std::cout << "Enter student lastname to show extended info: ";
    std::cin >> lastname;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::vector<const Student*> students = m_db.findStudentsByLastname(lastname);

    if(students.empty() == true)
    {
        std::cout << "Cannot find the students" << std::endl;
    }
    else
    {
        std::cout << "Selected students:" << std::endl;
        for(auto st : students)
        {
            st->showStudentEx();
            std::cout << std::endl << std::endl;
        }
    }
}

void ConsoleGUI::addStudentByUser(void) const
{
    std::string name;
    std::string lastname;
    std::string address;
    int indexNumber; 
    std::string pesel; 
    Gender gnr;
    std::cout << "Please enter:" << std::endl;
    std::cout << "Name:";
    std::cin >> name;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Lastname:";
    std::cin >> lastname;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Residential address:";
    std::getline(std::cin >> std::ws, address);
    std::cout << "Index number:";
    std::cin >> indexNumber;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "PESEL:";
    std::cin >> pesel;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Gender:";
    std::cin >> gnr;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    m_db.addStudent(std::make_unique<MathStudent>(name, lastname, address, indexNumber, pesel, gnr));

    std::cout << "Student added!" << std::endl;
}

void ConsoleGUI::removeStudentByUser(void) const
{
    std::string pesel;

    std::cout << "Enter the PESEL number of the student you want to remove from the database: ";
    std::cin >> pesel;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


    if(m_db.removeStudentByPesel(pesel) != true)
    {
        std::cout << "Wrong PESEL number! Could not be removed" << std::endl;
    }
    else
    {
        std::cout << "Removed!" << std::endl;
    }
}

void ConsoleGUI::modifyStudentByUser(void) const
{
    std::string pesel;
    std::cout << "Enter the PESEL number of the student you want to modify: ";
    std::cin >> pesel;

    bool isModified = m_db.modifyStudentByPesel(pesel);

    if(isModified == false)
    {
        std::cout << "The student could not be found" << std::endl;
    }
    else
    {
        std::cout << "Student modified!" << std::endl;
    }
}

void ConsoleGUI::sortStudentsByLastNameAtoZ(void) const
{
    m_db.sortStudents(StudentDatabase::SORT_BY_LASTNAME_A_TO_Z);
    std::cout << "Sorted student list:" << std::endl;
    m_db.displayStudents();
}

void ConsoleGUI::sortStudentsByLastNameZtoA(void) const
{
    m_db.sortStudents(StudentDatabase::SORT_BY_LASTNAME_Z_TO_A);
    std::cout << "Sorted student list:" << std::endl;
    m_db.displayStudents();
}

void ConsoleGUI::sortStudentsByIndexAscending(void) const
{
    m_db.sortStudents(StudentDatabase::SORT_BY_INDEX_ASCENDING);
    std::cout << "Sorted student list:" << std::endl;
    m_db.displayStudents();
}

void ConsoleGUI::sortStudentsByIndexDescending(void) const
{
    m_db.sortStudents(StudentDatabase::SORT_BY_INDEX_DESCENDING);
    std::cout << "Sorted student list:" << std::endl;
    m_db.displayStudents();
}

void ConsoleGUI::displayMenu(const MenuItem & selectedMenu) const 
{
    std::cout << "===========================================================================================" << std::endl;
    for (int i = 0; i < selectedMenu.subMenu.size(); i++) 
    {
        std::cout << i+1 << ". " << selectedMenu.subMenu[i].label << std::endl;
    }
    std::cout << "===========================================================================================" << std::endl;
    std::cout << "0. Wyjscie " << std::endl;
    std::cout << "===========================================================================================" << std::endl;
    std::cout << "Select option: ";
}

void ConsoleGUI::run() 
{
    if(m_mainMenu.label.empty())
    {
        std::cout << "[ERROR] Menu is not defined!";
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
            system("cls");
            continue;
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
    std::cout << "Press '0' to return: " << std::endl;
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