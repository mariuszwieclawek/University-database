#pragma once
#include <iostream>
#include <functional>
#include <stack>
#include <limits>
#include <memory>

#include "studentdatabase.hpp"
#include "mathStudent.hpp"

struct MenuItem {
    std::string label;
    std::function<void()> action;
    std::vector<MenuItem> subMenu;
};

class ConsoleGUI {
private:
    StudentDatabase & m_db;
    MenuItem m_mainMenu;
    bool m_isMenuEnabled;
public:
    ConsoleGUI(StudentDatabase &  db);

    void action1(void);

    void action4(void);

    void findStudentByLastname(void);
    void addStudentByUser(void);
    void removeStudentByUser(void);
    void modifyStudentByUser(void);

    void displayMenu(const MenuItem & selectedMenu);
    void run();

    void performSelectedAction(std::function<void()> action);
};

