#pragma once
#include "Entity.hpp"
#include <set>
#include <map>
#include <vector>

#define MIN_GRADE 0
#define MAX_GRADE 6

class Student : public Entity
{
private:
    std::string m_fieldOfStudy;
    std::set<std::string> m_subjects;
    std::map<std::string, std::vector<float>> m_grades;
    
public:
    Student(int indexNumber, const std::string & name, const std::string & lastname, const std::tm & birthDate, const std::string & address = "default",
            const std::string & pesel = "default", Gender gender = Gender::Default, const std::string & fldOfStudy = "default",
            const std::string & subjects = "default", const std::string & grades = "default");
                         
    Student(int && indexNumber, const std::string && name, const std::string && lastname, const std::tm && birthDate, const std::string && address = "default",
            const std::string && pesel = "default", Gender && gender = Gender::Default, const std::string && fldOfStudy = "default",
            const std::string && subjects = "default", const std::string && grades = "default");
                    
    Student(const Student &other);

    Student& operator==(const Student & other);

    std::string getFieldOfStudy(void) const;
    void setFieldOfStudy(const std::string & fld_of_study);
    std::set<std::string> getSubjects(void) const;
    void setSubjects(const std::set<std::string> & subjects);
    std::map<std::string, std::vector<float>> getGrades(void) const;
    void setGrades(const std::map<std::string, std::vector<float>> & grades);

    EntityType getEntityType(void) const override;

    std::string serialize(void) const override;
    std::string infoToString(void) const override;
    std::string extendedInfoToString(void) const override;

    std::unique_ptr<Entity> clone(void) const override;

    std::string showSubjects(void) const;
    bool addSubject(const std::string & subjectName);
    bool removeSubject(const std::string & subjectName);
    std::string showGrades(void) const;
    bool addGrade(const std::string & subject, float grade);
    bool removeGrade(const std::string & subject);
};