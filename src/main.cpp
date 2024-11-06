#include <iostream>
#include <memory>

#include "Entity.hpp"
#include "Student.hpp"
#include "UniversityDatabase.hpp"
#include "CommandLineInterface.hpp"



int main()
{
    // std::unique_ptr<Entity> student = std::make_unique<Student>("Mariusz", "Kowalski", "Czarna 21 33-300 Nowy Sacz",
    //                                                                 400201, "99020213134", Gender::Male);
    // student->show();

    // student->addSubject("English");
    // student->removeSubject("Statistics");

    // student->addGrade("Math", "Activity1", 5.0);
    // student->addGrade("Math", "Test1", 3.5);
    // student->addGrade("Physics", "Activity1", 4.5);
    // student->addGrade("Physics", "Test1", 4.5);
    // student->addGrade("Physics", "OralAnswer1", 4.5);
    // student->addGrade("Physics", "OralAnswer1", 4.5);
    // student->addGrade("asd", "OralAnswer1", 4.5);
    // student->addGrade("asd", "OralAnswer1", 6.1);
    // student->removeGrade("asd", "OralAnswer1");
    // student->removeGrade("Physics", "Test1");
    // student->removeGrade("Physics", "asdaasda");
    // student->showGrades();

    UniversityDatabase db;
    // db.addEntity(std::move(student));

    // student = std::make_unique<Student>("Michal", "Niemy", "Biala 221 30-302 Krakow",
    //                                         400202, "99020212345", Gender::Male);
    // student->addGrade("Math", "Activity1", 5.0);
    // student->addGrade("Math", "Test1", 3.5);
    // student->addGrade("Physics", "Activity1", 4.5);
    // student->addGrade("Physics", "Test1", 4.5);
    // student->showGrades();
    // db.addEntity(std::move(student));

    // student = std::make_unique<Student>("Andrzej", "Abacki", "Zolta 12a 30-302 Krakow",
    //                                         400203, "99020254321", Gender::Male);
    // student->addGrade("Math", "Activity1", 2.0);
    // student->addGrade("Math", "Test1", 2.5);
    // student->addGrade("Physics", "Activity1", 1.5);
    // student->addGrade("Physics", "Test1", 3.5);
    // student->showGrades();
    // db.addEntity(std::move(student));

    // db.sortStudentByLastname();
    // db.showEntities();

    // std::vector<Entity*> sts = db.findEntitiesByLastname("Abacki");
    // sts[0]->show();


    CommandLineInterface menu(db);
    menu.run();

    return 0;
}