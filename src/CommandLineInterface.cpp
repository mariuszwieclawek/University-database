#include "CommandLineInterface.hpp"
#include "Windows.h"
#include "sstream"
#include <conio.h>
#include <cctype> 


CommandLineInterface::CommandLineInterface(UniversityDatabase &  db) : m_db(db)
{
    auto action1 = [this]() { this->displayFieldsOfStudy(); };
    auto action2 = [this]() { this->displayStudentsForSelectedFieldOfStudy(); };
    auto action3 = [this]() { this->displaySubjectsForSelectedFieldOfStudy(); };
    auto action4 = [this]() { this->m_db.displayEntities(); };
    auto action5 = [this]() { this->displayEntitiesByLastname(); };
    auto action6 = [this]() { this->addEntityByUser(); };
    auto action7 = [this]() { this->removeEntityByUser(); };
    auto action8 = [this]() { this->modifyEntityByUser(); };
    auto action9 = [this]() { this->sortEntitiesByLastNameAtoZ(); };
    auto action10 = [this]() { this->sortEntitiesByLastNameZtoA(); };
    auto action11 = [this]() { this->sortEntitiesByIndexAscending(); };
    auto action12 = [this]() { this->sortEntitiesByIndexDescending(); };

    m_mainMenu =
    {
        "Main Menu", nullptr,
        {
            {"Fields of study list", action1, 
            {
                {"Enter field of study and display Student list", action2, {}},
                {"Enter field of study and display Subject list", action3, {}}
            }},
            {"List of entities at the university", action4, {}},
            {"Sort entity list", nullptr, 
            {
                {"Sort entities by lastname A to Z", action9, {}},
                {"Sort entities by lastname Z to A", action10, {}},
                {"Sort entities by index number ascending", action11, {}},
                {"Sort entities by index number descending", action12, {}},
            }},
            {"Search for entities", action5, {}},
            {"Add entity", action6, {}},
            {"Remove entity", action7, {}},
            {"Modify entity", action8, {}}
        }
    };
};

void CommandLineInterface::action1(void)
{
    std::cout << "hello" << std::endl;
}

void CommandLineInterface::displayFieldsOfStudy(void) const
{
    std::cout << "List of fields of study at the university:" << std::endl;
    std::set<std::string> fields_of_study = m_db.getFieldsOfStudy();
    for(auto fld_of_st : fields_of_study)
    {
        std::cout << "\t-" << fld_of_st << std::endl;
    }
    std::cout << std::endl;
}

void CommandLineInterface::displayStudentsForSelectedFieldOfStudy(void) const
{
    this->displayFieldsOfStudy();
    std::string fldOfStd;
    std::cout << "Please enter field of study: ";
    std::cin >> fldOfStd;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    m_db.displayEntitiesByFieldOfStudy(fldOfStd);
}

void CommandLineInterface::displaySubjectsForSelectedFieldOfStudy(void) const
{
    this->displayFieldsOfStudy();
    std::string fldOfStd;
    std::cout << "Please enter field of study: ";
    std::cin >> fldOfStd;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::set<std::string> subjects = m_db.getSubjectsForSelectedFieldOfStudy(fldOfStd);
    std::cout << "===========================================================================================" << std::endl;
    std::cout << "Subject list for " << fldOfStd << ":" << std::endl;
    for( auto & sub : subjects )
    {
        std::cout << "\t-" << sub << std::endl;
    }
}

void CommandLineInterface::displayEntitiesByLastname(void) const
{
    m_db.displayEntities();
    std::cout << "===========================================================================================" << std::endl << std::endl;
    std::string lastname;
    std::cout << "Enter entity lastname to show extended info: ";
    std::cin >> lastname;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::vector<const Entity*> entities = m_db.findEntitiesByLastname(lastname);

    if(entities.empty() == true)
    {
        std::cout << "Cannot find the entities" << std::endl;
    }
    else
    {
        std::cout << "Selected entities:" << std::endl;
        for(auto ent : entities)
        {
            ent->showExtented();
            std::cout << std::endl << std::endl;
        }
    }
}

void CommandLineInterface::addEntityByUser(void) const
{
    std::string name;
    std::string lastname;
    std::tm birthdate;
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

    std::cout << "Birthdate..." << std::endl << "\tDay:";
    std::cin >> birthdate.tm_mday;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "\tMonth:";
    std::cin >> birthdate.tm_mon;
    birthdate.tm_mon -= 1;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "\tYear:";
    std::cin >> birthdate.tm_year;
    birthdate.tm_year -= 1900;
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

    m_db.addEntity(std::make_unique<Student>(name, lastname, birthdate, address, indexNumber, pesel, gnr));

    std::cout << "Entity added!" << std::endl;
}

void CommandLineInterface::removeEntityByUser(void) const
{
    m_db.displayEntities();
    std::cout << "===========================================================================================" << std::endl;
    std::string pesel;

    std::cout << "Enter the PESEL number of the entity you want to remove from the database: ";
    std::cin >> pesel;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


    if(m_db.removeEntityByPesel(pesel) != true)
    {
        std::cout << "Wrong PESEL number! Could not be removed" << std::endl;
    }
    else
    {
        std::cout << "Removed!" << std::endl;
    }
}

void CommandLineInterface::modifyEntityByUser(void) const
{
    m_db.displayEntities();
    std::cout << "===========================================================================================" << std::endl;
    std::string pesel;
    std::cout << "Enter the PESEL number of the entity you want to modify: ";
    std::cin >> pesel;

    bool isModified = m_db.modifyEntityByPesel(pesel);

    if(isModified == false)
    {
        std::cout << "The entity could not be found" << std::endl;
    }
    else
    {
        std::cout << "Entity modified!" << std::endl;
    }
}

void CommandLineInterface::sortEntitiesByLastNameAtoZ(void) const
{
    m_db.sortEntities(UniversityDatabase::SORT_BY_LASTNAME_A_TO_Z);
    std::cout << "Sorted entity list:" << std::endl;
    m_db.displayEntities();
}

void CommandLineInterface::sortEntitiesByLastNameZtoA(void) const
{
    m_db.sortEntities(UniversityDatabase::SORT_BY_LASTNAME_Z_TO_A);
    std::cout << "Sorted entity list:" << std::endl;
    m_db.displayEntities();
}

void CommandLineInterface::sortEntitiesByIndexAscending(void) const
{
    m_db.sortEntities(UniversityDatabase::SORT_BY_INDEX_ASCENDING);
    std::cout << "Sorted entity list:" << std::endl;
    m_db.displayEntities();
}

void CommandLineInterface::sortEntitiesByIndexDescending(void) const
{
    m_db.sortEntities(UniversityDatabase::SORT_BY_INDEX_DESCENDING);
    std::cout << "Sorted entity list:" << std::endl;
    m_db.displayEntities();
}

void CommandLineInterface::displayMenu(const MenuItem & selectedMenu) const 
{
    std::cout << "===========================================================================================" << std::endl;
    for (int i = 0; i < selectedMenu.subMenu.size(); i++) 
    {
        std::cout << i+1 << ". " << selectedMenu.subMenu[i].label << std::endl;
    }
    std::cout << "===========================================================================================" << std::endl;
    std::cout << "0. Exit " << std::endl;
    std::cout << "===========================================================================================" << std::endl;
    std::cout << "Select option: ";
}

void CommandLineInterface::run() 
{
    if(m_mainMenu.label.empty())
    {
        std::cerr << "\t[ERROR]\t" + std::string(__func__) + " function failed" << std::endl;
        return;
    }

    char choice_ch;
    int choice_digit;
    MenuItem currentMenu = m_mainMenu;
    std::stack<MenuItem> menuStack;
    menuStack.push(currentMenu);
    m_isMenuEnabled = true;

    system("cls");

    MenuItem selectedOption;
    while (m_isMenuEnabled) 
    {
        displayMenu(currentMenu);

        /* Handle user input parameter*/
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
            selectedOption = currentMenu.subMenu[choice_digit - 1];
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
                    /* If action for current menu is defined call action */
                    if(currentMenu.action != nullptr)
                    {
                        currentMenu.action();
                    }
                }
            }      
        }
    }
}

void CommandLineInterface::exitFromSelectedAction()
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