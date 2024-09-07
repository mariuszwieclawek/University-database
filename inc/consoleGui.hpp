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

    void displayFieldsOfStudy(void) const;
    void displayStudentsForSelectedFieldOfStudy(void) const;
    void displayStudentsByLastname(void) const;

    void addStudentByUser(void) const;
    void removeStudentByUser(void) const;
    void modifyStudentByUser(void) const;
    void sortStudentsByLastNameAtoZ(void) const;
    void sortStudentsByLastNameZtoA(void) const;
    void sortStudentsByIndexAscending(void) const;
    void sortStudentsByIndexDescending(void) const;

    void displayMenu(const MenuItem & selectedMenu) const;
    void run();

    void exitFromSelectedAction();
};

