#include <iostream>
#include <student.hpp>
#include <mathStudent.hpp>
#include <database.hpp>
#include <memory>


    std::string m_name;
    std::string m_lastname;
    std::string m_address;
    int m_indexNumber;
    std::string m_pesel;
    Gender m_gender;
    std::set<std::string> m_subjects;

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
    return 0;
}