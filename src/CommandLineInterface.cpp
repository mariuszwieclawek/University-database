#include "CommandLineInterface.hpp"
#include <iostream>
#include <stack>
#include <limits>
#include <memory>
#include <sstream>
#include <conio.h>
#include <cctype>
#include "Windows.h"

#include "Student.hpp"
#include "Professor.hpp"
#include "EntityUtils.hpp"

CommandLineInterface::CommandLineInterface(UniversityDatabase &  db) : m_db(db)
{
    auto action10 = [this]() { this->displayEntities(); };
    auto action20 = [this]() { this->sortEntitiesByLastNameAtoZ(); };
    auto action21 = [this]() { this->sortEntitiesByLastNameZtoA(); };
    auto action22 = [this]() { this->sortEntitiesByIndexAscending(); };
    auto action23 = [this]() { this->sortEntitiesByIndexDescending(); };
    auto action24 = [this]() { this->sortEntitiesByEntityTypeAtoZ(); };
    auto action25 = [this]() { this->sortEntitiesByEntityTypeZtoA(); };
    auto action30 = [this]() { this->displayEntitiesByLastname(); };
    auto action40 = [this]() { this->addEntityByUser(); };
    auto action50 = [this]() { this->removeEntityByUser(); };
    auto action60 = [this]() { this->modifyEntityByUser(); };


    m_mainMenu =
    {
        "Main Menu", nullptr,
        {
            {"List of entities at the university", action10, {}},
            {"Sort entity list", nullptr, 
            {
                {"Sort entities by lastname A to Z", action20, {}},
                {"Sort entities by lastname Z to A", action21, {}},
                {"Sort entities by index number ascending", action22, {}},
                {"Sort entities by index number descending", action23, {}},
                {"Sort entities by Entity Type A to Z", action24, {}},
                {"Sort entities by Entity Type Z to A", action25, {}},
            }},
            {"Search for entities", action30, {}},
            {"Add entity", action40, {}},
            {"Remove entity", action50, {}},
            {"Modify entity", action60, {}}
        }
    };
};

void CommandLineInterface::displayEntities(void) const
{
    std::cout << "===================================================================================================================================================" << std::endl;
    std::cout << "| Index | Entity type | Name | Last name | Birthday | Address | PESEL | Gender | Field of study | Subjects | Grades | Academic Title | Department |" << std::endl;
    std::cout << "===================================================================================================================================================" << std::endl;
    m_db.showEntities();
    std::cout << "===================================================================================================================================================" << std::endl << std::endl;

    std::set<EntityType> ent_types = m_db.getEntityTypes();
    std::map<int, EntityType> ent_type_map;

    std::cout << "Select Entity Type to show list: " << std::endl;
    int iter = 1;
    for( const auto & ent_type : ent_types)
    {
        std::cout << iter << "." << ent_type << std::endl;
        ent_type_map.insert({iter, ent_type});
        iter++;
    }

    /* Handle user input parameter*/
    char choice_ch;
    int choice_digit;
    while(true)
    {
        choice_ch = _getch();
        if(isdigit(choice_ch))
        {
            choice_digit = choice_ch - '0'; // convert to digit
            /* check if map contains selected digit */
            if(ent_type_map.find(choice_digit) != ent_type_map.end()) break;
        }   
    }
    
    EntityType ent_type = ent_type_map[choice_digit];

    std::cout << "===================================================================================================================================================" << std::endl;
    std::cout << "| Index | Entity type | Name | Last name | Birthday | Address | PESEL | Gender | Field of study | Subjects | Grades | Academic Title | Department |" << std::endl;
    std::cout << "===================================================================================================================================================" << std::endl;
    m_db.showEntitiesByEntityType(ent_type);
    std::cout << "===================================================================================================================================================" << std::endl << std::endl;
}

void CommandLineInterface::displayEntitiesAll(void) const
{
    std::cout << "===================================================================================================================================================" << std::endl;
    std::cout << "| Index | Entity type | Name | Last name | Birthday | Address | PESEL | Gender | Field of study | Subjects | Grades | Academic Title | Department |" << std::endl;
    std::cout << "===================================================================================================================================================" << std::endl;
    m_db.showEntities();
    std::cout << "===================================================================================================================================================" << std::endl << std::endl;
}

void CommandLineInterface::displayEntitiesByLastname(void) const
{
    this->displayEntitiesAll();

    std::string lastname;
    std::cout << "Enter entity lastname to show extended info: ";
    std::getline(std::cin,lastname);

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
    std::map<int,std::string> digit_to_ent_type = 
    {
        {1, "Student"},
        {2, "Professor"},
    };
    char choice_ch;
    int choice_digit;

    std::cout << "Select Entity Type:" << std::endl;
    for( const auto & [digit, ent_type] : digit_to_ent_type)
    {
        std::cout << digit << "." << ent_type << std::endl;
    }
    std::cout << "Enter number..." << std::endl << std::endl;

    /* Handle user input parameter*/
    while(true)
    {
        choice_ch = _getch();
        if(isdigit(choice_ch))
        {
            choice_digit = choice_ch - '0'; // convert to digit
            /* check if map contains selected digit */
            if(digit_to_ent_type.find(choice_digit) != digit_to_ent_type.end()) break;
        }   
    }
    
    if("Student" == digit_to_ent_type[choice_digit])
    {
        this->addStudentByUser();
    }
    else if("Professor" == digit_to_ent_type[choice_digit])
    {
        this->addProfessorByUser();
    }
    else
    {
        /*TBD*/
    }
}

void CommandLineInterface::addStudentByUser(void) const
{
    std::string input;
    int indexNumber;
    std::string name;
    std::string lastname;
    std::tm birthdate;
    std::string address;
    std::string pesel; 
    Gender gnr;
    std::string fieldofstudy;
    std::string subjects;
    std::string grades;
    std::cout << "Please enter:" << std::endl;

    std::cout << "Index number:";
    std::getline(std::cin, input);
    indexNumber = stoi(input);

    std::cout << "Name:";
    std::getline(std::cin, name);

    std::cout << "Lastname:";
    std::getline(std::cin, lastname);

    std::cout << "Birthdate..." << std::endl << "\tDay:";
    std::getline(std::cin, input);
    birthdate.tm_mday = stoi(input);
    std::cout << "\tMonth:";
    std::getline(std::cin, input);
    birthdate.tm_mon = stoi(input);
    birthdate.tm_mon -= 1;
    std::cout << "\tYear:";
    std::getline(std::cin, input);
    birthdate.tm_year = stoi(input);
    birthdate.tm_year -= 1900;

    std::cout << "Residential address:";
    std::getline(std::cin >> std::ws, address);

    std::cout << "PESEL:";
    std::getline(std::cin, pesel);

    std::cout << "Gender:";
    std::getline(std::cin, input);
    gnr = stringToGender(input);

    std::cout << "Field of study:";
    std::getline(std::cin, fieldofstudy);

    std::cout << "Subjects (format: 'Math; Computer Science; Psychics'):";
    std::getline(std::cin, subjects);

    std::cout << "Grades (format: 'Math={2.5 3 4.5 2};Psychics={3.5 5 3.5 4};' ):";
    std::getline(std::cin, grades);

    m_db.addEntity(std::make_unique<Student>(indexNumber, name, lastname, birthdate, address, pesel, gnr, fieldofstudy, subjects, grades));

    std::cout << "Student added!" << std::endl;
}

void CommandLineInterface::addProfessorByUser(void) const
{
    std::string input;
    int indexNumber;
    EntityType entitytype;
    std::string name;
    std::string lastname;
    std::tm birthdate;
    std::string address;
    std::string pesel; 
    Gender gnr;
    AcademicTitle acdtitle;
    Department department;
    std::cout << "Please enter:" << std::endl;

    std::cout << "Index number:";
    std::getline(std::cin, input);
    indexNumber = stoi(input);

    entitytype = EntityType::Professor;

    std::cout << "Name:";
    std::getline(std::cin, name);

    std::cout << "Lastname:";
    std::getline(std::cin, lastname);

    std::cout << "Birthdate..." << std::endl << "\tDay:";
    std::getline(std::cin, input);
    birthdate.tm_mday = stoi(input);
    std::cout << "\tMonth:";
    std::getline(std::cin, input);
    birthdate.tm_mon = stoi(input);
    birthdate.tm_mon -= 1;
    std::cout << "\tYear:";
    std::getline(std::cin, input);
    birthdate.tm_year = stoi(input);
    birthdate.tm_year -= 1900;

    std::cout << "Residential address:";
    std::getline(std::cin >> std::ws, address);

    std::cout << "PESEL:";
    std::getline(std::cin, pesel);

    std::cout << "Gender:";
    std::getline(std::cin, input);
    gnr = stringToGender(input);

    std::cout << "Academic Title:";
    std::getline(std::cin, input);
    acdtitle = stringToAcademicTitle(input);

    std::cout << "Department:";
    std::getline(std::cin, input);
    department = stringToDepartment(input);

    m_db.addEntity(std::make_unique<Professor>(indexNumber, name, lastname, birthdate, address, pesel, gnr, acdtitle, department));

    std::cout << "Professor added!" << std::endl;
}

void CommandLineInterface::removeEntityByUser(void) const
{
    this->displayEntitiesAll();
    
    std::string pesel;

    std::cout << "Enter the PESEL number of the entity you want to remove from the database: ";
    std::getline(std::cin, pesel);

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
    this->displayEntitiesAll();
    
    std::string pesel;
    std::cout << "Enter the PESEL number of the entity you want to modify: ";
    std::getline(std::cin, pesel);

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
    this->displayEntitiesAll();
}

void CommandLineInterface::sortEntitiesByLastNameZtoA(void) const
{
    m_db.sortEntities(UniversityDatabase::SORT_BY_LASTNAME_Z_TO_A);
    std::cout << "Sorted entity list:" << std::endl;
    this->displayEntitiesAll();
}

void CommandLineInterface::sortEntitiesByIndexAscending(void) const
{
    m_db.sortEntities(UniversityDatabase::SORT_BY_INDEX_ASCENDING);
    std::cout << "Sorted entity list:" << std::endl;
    this->displayEntitiesAll();
}

void CommandLineInterface::sortEntitiesByIndexDescending(void) const
{
    m_db.sortEntities(UniversityDatabase::SORT_BY_INDEX_DESCENDING);
    std::cout << "Sorted entity list:" << std::endl;
    this->displayEntitiesAll();
}

void CommandLineInterface::sortEntitiesByEntityTypeAtoZ(void) const
{
    m_db.sortEntities(UniversityDatabase::SORT_BY_ENTITY_TYPE_A_TO_Z);
    std::cout << "Sorted entity list:" << std::endl;
    this->displayEntitiesAll();
}

void CommandLineInterface::sortEntitiesByEntityTypeZtoA(void) const
{
    m_db.sortEntities(UniversityDatabase::SORT_BY_ENTITY_TYPE_Z_TO_A);
    std::cout << "Sorted entity list:" << std::endl;
    this->displayEntitiesAll();
}

void CommandLineInterface::displayMenu(const MenuItem & selectedMenu) const 
{
    std::cout << "===================================================================================================================================================" << std::endl;
    for (int i = 0; i < selectedMenu.subMenu.size(); i++) 
    {
        std::cout << i+1 << ". " << selectedMenu.subMenu[i].label << std::endl;
    }
    std::cout << "===================================================================================================================================================" << std::endl;
    std::cout << "0. Exit " << std::endl;
    std::cout << "===================================================================================================================================================" << std::endl;
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

    std::cout << "===================================================================================================================================================" << std::endl;
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