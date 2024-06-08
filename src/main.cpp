#include <iostream>
#include <memory>

#include "student.hpp"
#include "mathStudent.hpp"
#include "studentdatabase.hpp"
#include "consoleGui.hpp"



int main()
{
    // std::unique_ptr<Student> student = std::make_unique<MathStudent>("Mariusz", "Kowalski", "Czarna 21 33-300 Nowy Sacz",
    //                                                                 400201, "99020213134", Gender::Male);
    // student->showStudent();
    // student->showSubjects();
    // student->addSubject("English");
    // student->removeSubject("Statistics");
    // student->removeSubject("asd");
    // student->showSubjects();

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

    StudentDatabase db;
    // db.addStudent(std::move(student));

    // student = std::make_unique<MathStudent>("Michal", "Niemy", "Biala 221 30-302 Krakow",
    //                                         400202, "99020212345", Gender::Male);
    // student->addGrade("Math", "Activity1", 5.0);
    // student->addGrade("Math", "Test1", 3.5);
    // student->addGrade("Physics", "Activity1", 4.5);
    // student->addGrade("Physics", "Test1", 4.5);
    // student->showGrades();
    // db.addStudent(std::move(student));

    // student = std::make_unique<MathStudent>("Andrzej", "Abacki", "Zolta 12a 30-302 Krakow",
    //                                         400203, "99020254321", Gender::Male);
    // student->addGrade("Math", "Activity1", 2.0);
    // student->addGrade("Math", "Test1", 2.5);
    // student->addGrade("Physics", "Activity1", 1.5);
    // student->addGrade("Physics", "Test1", 3.5);
    // student->showGrades();
    // db.addStudent(std::move(student));

    // db.sortStudentByLastname();
    // db.displayStudents();

    // std::vector<Student*> sts = db.findStudentByLastname("Abacki");
    // sts[0]->showStudent();


    ConsoleGUI menu(db);
    menu.run();

    return 0;
}