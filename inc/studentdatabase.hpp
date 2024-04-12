#pragma once
#include <vector>
#include <student.hpp>
#include <memory>

class StudentDatabase
{
private:
    std::vector<std::unique_ptr<Student>> m_students;
public:
    StudentDatabase(void){};

    void addStudent(std::unique_ptr<Student> student);
    bool removeStudentByPesel(const std::string & pesel);

    std::vector<Student*> findStudentByLastname(const std::string & lastname);

    void sortStudentByLastname(void);

    void displayStudents(void) const;
};