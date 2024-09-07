#pragma once
#include <string>
#include <vector>

class Student
{
public:
    virtual std::vector<std::string> getStudent(void) const = 0;
    virtual std::string getName(void) const = 0;
    virtual void setName(const std::string & name) = 0;
    virtual std::string getLastname(void) const = 0;
    virtual void getLastname(const std::string & lastname) = 0;
    virtual std::string getPesel(void) const = 0;
    virtual void setPesel(const std::string & name) = 0;
    virtual int getIndex(void) const = 0;
    virtual void setIndex(const int & index) = 0;
    virtual std::string getFieldOfStudy(void) const = 0;

    virtual void showStudent(void) const = 0;
    virtual void showStudentEx(void) const = 0;

    virtual void modifyStudent(void) = 0;

    virtual void showSubjects(void) const = 0;
    virtual bool addSubject(const std::string & subjectName) = 0;
    virtual bool removeSubject(const std::string & subjectName) = 0;

    virtual void showGrades(void) const = 0;
    virtual bool addGrade(const std::string & subject, const std::string & comment, float grade) = 0;
    virtual bool removeGrade(const std::string & subject, const std::string & comment) = 0;
};