#pragma once
#include <vector>
#include <student.hpp>
#include <memory>
#include <fstream>
#include <set>

class StudentDatabase
{
private:
    std::vector<std::unique_ptr<Student>> m_students;
    std::string m_studentsFilename = "../database/students.csv";
    std::fstream m_file;

    static bool compareByLastnameAtoZ(const std::unique_ptr<Student>& a, const std::unique_ptr<Student>& b);
    static bool compareByLastnameZtoA(const std::unique_ptr<Student>& a, const std::unique_ptr<Student>& b);
    static bool compareByIndexAscending(const std::unique_ptr<Student>& a, const std::unique_ptr<Student>& b);
    static bool compareByIndexDescending(const std::unique_ptr<Student>& a, const std::unique_ptr<Student>& b);

    void appendToCSV(std::fstream& file, const std::vector<std::string>& data);
    bool isCSVFileEmpty(std::fstream& file);
    void readStudentsFromCSV(std::fstream& file);
    void saveAllStudentsToCSV(void);
public:

    enum SortOrder {
        SORT_BY_LASTNAME_A_TO_Z = 0,
        SORT_BY_LASTNAME_Z_TO_A = 1,
        SORT_BY_INDEX_ASCENDING = 2,
        SORT_BY_INDEX_DESCENDING = 3,
    };

    StudentDatabase(void);
    ~StudentDatabase(void);

    void addStudent(std::unique_ptr<Student> student);
    bool removeStudentByPesel(const std::string & pesel);
    std::vector<const Student*> findStudentsByLastname(const std::string & lastname);
    bool modifyStudentByPesel(const std::string & pesel);
    void sortStudents(SortOrder order);

    std::set<std::string> getFieldsOfStudy(void) const;
    std::set<std::string> getSubjectsForSelectedFieldOfStudy(const std::string & fldOfStd) const;
    void displayStudents(void) const;
    void displayStudentsByFieldOfStudy(const std::string & fldOfStd) const;
};