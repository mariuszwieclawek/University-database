#pragma once
#include <vector>
#include <student.hpp>
#include <memory>
#include <fstream>

class StudentDatabase
{
private:
    std::vector<std::unique_ptr<Student>> m_students;
    std::string m_studentsFilename = "../output/students.csv";
    std::fstream m_file;
public:
    StudentDatabase(void);
    ~StudentDatabase(void);

    void appendToCSV(std::fstream& file, const std::vector<std::string>& data);
    void saveAllStudentsToCSV(void);
    bool isCSVFileEmpty(std::fstream& file);
    void readStudentsFromCSV(std::fstream& file);

    void addStudent(std::unique_ptr<Student> student);
    bool removeStudentByPesel(const std::string & pesel);

    std::vector<Student*> findStudentByLastname(const std::string & lastname);
    Student* findStudentByPesel(const std::string & pesel);

    void sortStudentByLastname(void);

    void displayStudents(void) const;
};