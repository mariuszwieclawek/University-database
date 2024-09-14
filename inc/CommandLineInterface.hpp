#pragma once
#include <iostream>
#include <functional>
#include <stack>
#include <limits>
#include <memory>

#include "UniversityDatabase.hpp"
#include "Student.hpp"

struct MenuItem {
    std::string label;
    std::function<void()> action;
    std::vector<MenuItem> subMenu;
};

class CommandLineInterface {
private:
    UniversityDatabase & m_db;
    MenuItem m_mainMenu;
    bool m_isMenuEnabled;
public:
    CommandLineInterface(UniversityDatabase &  db);

    void action1(void);

    void displayFieldsOfStudy(void) const;
    void displayStudentsForSelectedFieldOfStudy(void) const;
    void displaySubjectsForSelectedFieldOfStudy(void) const;
    void displayEntitiesByLastname(void) const;

    void addEntityByUser(void) const;
    void removeEntityByUser(void) const;
    void modifyEntityByUser(void) const;
    void sortEntitiesByLastNameAtoZ(void) const;
    void sortEntitiesByLastNameZtoA(void) const;
    void sortEntitiesByIndexAscending(void) const;
    void sortEntitiesByIndexDescending(void) const;

    void displayMenu(const MenuItem & selectedMenu) const;
    void run();

    void exitFromSelectedAction();
};

