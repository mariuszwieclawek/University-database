#include <iostream>
#include <memory>
#include <functional>
#include <stack>

#include "student.hpp"
#include "mathStudent.hpp"
#include "studentdatabase.hpp"


struct MenuItem {
    std::string label;
    std::function<void()> action;
    std::vector<MenuItem> subMenu;
};

class ConsoleGUI {
private:
    StudentDatabase & m_db;
    MenuItem m_mainMenu;
public:
    ConsoleGUI(StudentDatabase &  db) : m_db(db)
    {
        auto action1 = [this]() { this->action1(); };
        auto action2 = [this]() { this->m_db.displayStudents(); };
        auto action3 = [this]() { this->addStudentByUser(); };
        m_mainMenu =
        {
            "Menu główne", action1,
            {
                {"Lista kierunkow na uczelni", nullptr, {
                    {"Podopcja 1", action1, {}},
                    {"Podopcja 2", action1, {}}
                }},
                {"Lista studentow na uczelni", action2, {}},
                {"Dodaj studenta", action3, {}},
                {"Usun studenta", action1, {}},
                {"Zakoncz program", action1, {}}
            }
        };
    };

    void action1(void)
    {
        std::cout << "hello\n";
    }

    void addStudentByUser(void)
    {
        std::string name;
        std::string lastname;
        std::string address;
        int indexNumber; 
        std::string pesel; 
        Gender gnr;
        std::cout << "Prosze wpisac:\nImie:";
        std::cin >> name;
        std::cout << "Nazwisko:";
        std::cin >> lastname;
        std::cout << "Adres:";
        std::cin >> address;
        std::cout << "Numer indeksu:";
        std::cin >> indexNumber;
        std::cout << "Pesel:";
        std::cin >> pesel;

        m_db.addStudent(std::make_unique<MathStudent>(name, lastname, address, indexNumber, pesel));

        std::cout << "Dodano studenta!\n";
    }

    void displayMenu(const std::vector<MenuItem>& menu) 
    {
        for (int i = 0; i < menu.size(); ++i) {
            if( i == (menu.size() - 1))
            {
                std::cout << "0. " << menu[i].label << std::endl;
            }
            else
            {
                std::cout << i+1 << ". " << menu[i].label << std::endl;
            }
        }
        std::cout << "Wybierz opcje: ";
    }

    void run() 
    {
        if(m_mainMenu.label.empty())
        {
            std::cout << "[ERROR] Zdefiniuj menu w konstruktorze ConsoleGUI!";
            return;
        }

        int choice;
        std::vector<MenuItem> currentMenu = m_mainMenu.subMenu.empty() ? std::vector<MenuItem>{m_mainMenu} : m_mainMenu.subMenu;
        std::stack<std::vector<MenuItem>> menuStack;

        while (true) 
        {
            system("cls");
            displayMenu(currentMenu);

            std::cin >> choice;
            if (choice < 0 || choice > currentMenu.size()) {
                std::cout << "Nieprawidlowy wybor. Sprobuj ponownie." << std::endl;
                continue;
            }

            // if(!menuStack.empty())
            // {
            //     menuStack.push(currentMenu);
            // }

            // if (choice == 0 && menuStack.empty())
            // {
            //     break;
            // }

            // if (choice == 0 && !menuStack.empty())
            // {
            //     menuStack.pop();
            // }

            MenuItem selectedOption = currentMenu[choice - 1];
            if (selectedOption.subMenu.empty()) 
            {
                system("cls");
                std::cout << selectionWrapper(selectedOption.label) ;
            } 
            else 
            {
                currentMenu = selectedOption.subMenu;
            }

            if (selectedOption.action != nullptr)
            {
                selectedOption.action();
                while(choice != 0)
                {
                    std::cout << "0. Wyjscie " << std::endl;
                    std::cin >> choice;
                }
            }
        }
    }

    std::string selectionWrapper(std::string txt) 
    {
        return std::string("================================================\n") +
            " Wybrano: " + txt +
            "\n================================================\n";
    }


};


int main()
{
    std::unique_ptr<Student> student = std::make_unique<MathStudent>("Mariusz", "Kowalski");
    student->showStudent();
    student->showSubjects();
    student->addSubject("English");
    student->removeSubject("Statistics");
    student->removeSubject("asd");
    student->showSubjects();

    student->addGrade("Math", "Activity1", 5.0);
    student->addGrade("Math", "Test1", 3.5);
    student->addGrade("Physics", "Activity1", 4.5);
    student->addGrade("Physics", "Test1", 4.5);
    student->addGrade("Physics", "OralAnswer1", 4.5);
    student->addGrade("Physics", "OralAnswer1", 4.5);
    student->addGrade("asd", "OralAnswer1", 4.5);
    student->addGrade("asd", "OralAnswer1", 6.1);
    student->removeGrade("asd", "OralAnswer1");
    student->removeGrade("Physics", "Test1");
    student->removeGrade("Physics", "asdaasda");
    student->showGrades();

    StudentDatabase db;
    db.addStudent(std::move(student));

    student = std::make_unique<MathStudent>("Michal", "Niemy");
    student->addGrade("Math", "Activity1", 5.0);
    student->addGrade("Math", "Test1", 3.5);
    student->addGrade("Physics", "Activity1", 4.5);
    student->addGrade("Physics", "Test1", 4.5);
    student->showGrades();
    db.addStudent(std::move(student));

    student = std::make_unique<MathStudent>("Andrzej", "Abacki");
    student->addGrade("Math", "Activity1", 2.0);
    student->addGrade("Math", "Test1", 2.5);
    student->addGrade("Physics", "Activity1", 1.5);
    student->addGrade("Physics", "Test1", 3.5);
    student->showGrades();
    db.addStudent(std::move(student));

    db.sortStudentByLastname();
    db.displayStudents();

    std::vector<Student*> sts = db.findStudentByLastname("Abacki");
    sts[0]->showStudent();




    ConsoleGUI menu(db);
    menu.run();

    return 0;
}