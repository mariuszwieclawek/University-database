#pragma once
#include "UniversityDatabase.hpp"
#include <functional>

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

    //void displayFieldsOfStudy(void) const;
    //void displayEntitiesForSelectedFieldOfStudy(void) const;
    void displayEntitiesByLastname(void) const;

    void addEntityByUser(void) const;
    void addStudentByUser(void) const;
    void addProfessorByUser(void) const;
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

