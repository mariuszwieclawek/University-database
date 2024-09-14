#pragma once
#include <string>
#include <vector>
#include <set>

class Entity
{
public:
    virtual std::string serialize(void) const = 0;
    virtual std::string getName(void) const = 0;
    virtual void setName(const std::string & name) = 0;
    virtual std::string getLastname(void) const = 0;
    virtual void setLastname(const std::string & lastname) = 0;
    virtual std::string getPesel(void) const = 0;
    virtual void setPesel(const std::string & name) = 0;
    virtual int getIndex(void) const = 0;
    virtual void setIndex(const int & index) = 0;
    virtual std::set<std::string> getMandatorySubjects(void) const = 0;
    virtual std::string getFieldOfStudy(void) const = 0;

    virtual void show(void) const = 0;
    virtual void showExtented(void) const = 0;

    virtual void modify(void) = 0;

    virtual void showSubjects(void) const = 0;
    virtual bool addSubject(const std::string & subjectName) = 0;
    virtual bool removeSubject(const std::string & subjectName) = 0;

    virtual void showGrades(void) const = 0;
    virtual bool addGrade(const std::string & subject, const std::string & comment, float grade) = 0;
    virtual bool removeGrade(const std::string & subject, const std::string & comment) = 0;
};