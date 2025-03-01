#include "CommandLineInterface.hpp"
#include <iostream>
#include <stack>
#include <limits>
#include <memory>
#include <sstream>
#include <cctype>
#include "Student.hpp"
#include "Professor.hpp"
#include "EntityUtils.hpp"


#ifdef _WIN32
    #include <conio.h>
    char my_getch() 
    {
        return _getch();
    }
#else
    #include <termios.h>
    #include <unistd.h>
    char my_getch() 
    {
        struct termios oldt, newt;
        char ch;

        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);

        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

        return ch;
    }
#endif

#ifdef _WIN32
    #include <windows.h>
    void clearScreen() 
    {
        system("cls");
    }
#else
    #include <cstdlib>
    void clearScreen() 
    {
        std::system("clear");
    }
#endif

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
        choice_ch = my_getch();
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
            std::string student_str = ent->extendedInfoToString();
            std::cout << student_str << std::endl << std::endl;
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
        choice_ch = my_getch();
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

    std::cout << "Subjects (format: 'Math; Computer Science; Physics'):";
    std::getline(std::cin, subjects);

    std::cout << "Grades (format: 'Math={2.5 3 4.5 2};Physics={3.5 5 3.5 4};' ):";
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
    
    std::string pesel_input;
    std::cout << "Enter the PESEL number of the entity you want to modify: ";
    std::getline(std::cin, pesel_input);

    const Entity& entity = m_db.findEntityByPesel(pesel_input);

    if (auto studentPtr = dynamic_cast<const Student*>(&entity)) 
    {
        Student std = *studentPtr;
        std::cout << "Actual data for student:" << std::endl;
        std::cout << std.extendedInfoToString();
        std::cout << "Modification started. Please enter new values:" << std::endl;
        std::string input;

        std::cout << "Current Index number: " << std.getIndex() << std::endl << "Enter new Index number or skip(Enter): ";
        std::getline(std::cin, input);
        if (!input.empty()) std.setIndex(std::stoi(input));

        std::cout << "Current Name: " << std.getName() << std::endl << "Enter new Name or skip(Enter): ";
        std::getline(std::cin, input);
        if (!input.empty()) std.setName(input);

        std::cout << "Current Last name: " << std.getLastname() << std::endl << "Enter new Last name or skip(Enter): ";
        std::getline(std::cin, input);
        if (!input.empty()) std.setLastname(input);;

        std::cout << "Current birthday date: " << TmToString(std.getBirthdayDate(), "%d.%m.%Y") << std::endl << "Enter new Birthday date or skip(Enter): ";
        std::getline(std::cin, input);
        if (!input.empty()) std.setBirthdayDate(stringToTm(input, "%d.%m.%Y"));

        std::cout << "Current Address: " << std.getAddress() << std::endl << "Enter new Address or skip(Enter): ";
        std::getline(std::cin, input);
        if (!input.empty()) std.setAddress(input);

        std::cout << "Current PESEL: " << std.getPesel() << std::endl << "Enter new PESEL or skip(Enter): ";
        std::getline(std::cin, input);
        if (!input.empty()) std.setPesel(input);

        std::cout << "Current Gender: " << std.getGender() << std::endl << "Enter new Gender or skip(Enter): ";
        std::getline(std::cin, input);
        if (!input.empty()) std.setGender(stringToGender(input));

        std::cout << "Current Field of Study: " << std.getFieldOfStudy() << std::endl << "Enter new Field of Study or skip(Enter): ";
        std::getline(std::cin, input);
        if (!input.empty()) std.setFieldOfStudy(input);

        std::cout << "Current Subjects:" << std::endl;
        std::cout << std.showSubjects();
        std::cout << "Enter new Subjects(format: 'Math; Computer Science; Physics') or skip(Enter): ";
        std::getline(std::cin, input);
        if (!input.empty()) std.setSubjects(stringToSet(input));
    
        std::cout << "Current Grades: " << std::endl;
        std::cout << std.showGrades();
        std::cout << "Enter new Grades(format: 'Math={2.5 3 4.5 2};Physics={3.5 5 3.5 4};' ) or skip(Enter): ";
        std::getline(std::cin, input);
        if (!input.empty()) std.setGrades(parseGrades(input));

        if(m_db.modifyEntityByPesel(pesel_input, std::make_unique<Student>(std)) != true)
        {
            std::cout << "Nie znaleziono " << std::endl;
        }

    }
    else if (auto professorPtr = dynamic_cast<const Professor*>(&entity)) 
    {
        Professor prof = *professorPtr;
        std::cout << "Actual data for professor:" << std::endl;
        std::cout << prof.extendedInfoToString();
        std::cout << "Modification started. Please enter new values:" << std::endl;
        std::string input;

        std::cout << "Current Index number: " << prof.getIndex() << std::endl << "Enter new Index number or skip(Enter): ";
        std::getline(std::cin, input);
        if (!input.empty()) prof.setIndex(std::stoi(input));

        std::cout << "Current Name: " << prof.getName() << std::endl << "Enter new Name or skip(Enter): ";
        std::getline(std::cin, input);
        if (!input.empty()) prof.setName(input);

        std::cout << "Current Last name: " << prof.getLastname() << std::endl << "Enter new Last name or skip(Enter): ";
        std::getline(std::cin, input);
        if (!input.empty()) prof.setLastname(input);;

        std::cout << "Current birthday date: " << TmToString(prof.getBirthdayDate(), "%d.%m.%Y") << std::endl << "Enter new Birthday date or skip(Enter): ";
        std::getline(std::cin, input);
        if (!input.empty()) prof.setBirthdayDate(stringToTm(input, "%d.%m.%Y"));

        std::cout << "Current Address: " << prof.getAddress() << std::endl << "Enter new Address or skip(Enter): ";
        std::getline(std::cin, input);
        if (!input.empty()) prof.setAddress(input);

        std::cout << "Current PESEL: " << prof.getPesel() << std::endl << "Enter new PESEL or skip(Enter): ";
        std::getline(std::cin, input);
        if (!input.empty()) prof.setPesel(input);

        std::cout << "Current Gender: " << prof.getGender() << std::endl << "Enter new Gender or skip(Enter): ";
        std::getline(std::cin, input);
        if (!input.empty()) prof.setGender(stringToGender(input));

        std::cout << "Current Academic Title: " << academicTitleToString(prof.getAcademicTitle()) << std::endl << "Enter new Academic Title or skip(Enter): ";
        std::getline(std::cin, input);
        if (!input.empty()) prof.setAcademicTitle(stringToAcademicTitle(input)); 

        std::cout << "Current Department: " << departmentToString(prof.getDepartment()) << std::endl << "Enter new Department or skip(Enter): ";
        std::getline(std::cin, input);
        if (!input.empty()) prof.setDepartment(stringToDepartment(input)); 

        if(m_db.modifyEntityByPesel(pesel_input, std::make_unique<Professor>(prof)) != true)
        {
            std::cout << "Nie znaleziono " << std::endl;
        }
    }
    else
    {
        //
    }

    std::cout << "Zmodyfikowano!" << std::endl;
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

    clearScreen();

    MenuItem selectedOption;
    while (m_isMenuEnabled) 
    {
        displayMenu(currentMenu);

        /* Handle user input parameter*/
        choice_ch = my_getch();
        if (isdigit(choice_ch)) 
        { 
            choice_digit = choice_ch - '0'; // convert to digit
        } 
        else 
        {
            clearScreen();
            continue;
        }
        clearScreen();

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
        choice_ch = my_getch();
        if (isdigit(choice_ch)) 
        { 
            choice_digit = choice_ch - '0'; // convert to digit
        } 

        if(choice_digit == 0)
        {
            clearScreen();
            break;
        }
    }
}