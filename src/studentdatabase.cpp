#include "studentdatabase.hpp"
#include <iostream>

void StudentDatabase::addStudent(std::unique_ptr<Student> student)
{
    m_students.push_back(std::move(student));
}

bool StudentDatabase::removeStudentByPesel(const std::string & pesel)
{
    auto it = std::remove_if(m_students.begin(), m_students.end(),
                                [&pesel](const std::unique_ptr<Student> & st){return st->getPesel() == pesel;} );
                                
    m_students.erase(it, m_students.end());

    //TO DO
    return true;
}

std::vector<Student*> StudentDatabase::findStudentByLastname(const std::string & lastname)
{
    std::vector<Student*> foundStudents;
    for(const auto & s : m_students)
    {
        if(s->getLastname() == lastname)
        {
            foundStudents.push_back(s.get());
        }
    }

    return foundStudents;
}

void StudentDatabase::sortStudentByLastname(void)
{
    std::sort(m_students.begin(), m_students.end(), 
    [](const std::unique_ptr<Student> & st1, const std::unique_ptr<Student> & st2){return st1->getLastname() < st2->getLastname();});
}

void StudentDatabase::displayStudents(void) const
{
    if (m_students.empty()) {
        std::cout << "Baza danych jest pusta." << std::endl;
        return;
    }

    std::cout << "Lista studentow:" << std::endl;
    for(const auto & st : m_students)
    {
        st->showStudent();
    }
}