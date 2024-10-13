#pragma once
#include "Entity.hpp"
#include <string>
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
    std::map<std::string, std::vector<float>> m_averageGrades;
    
public:
    Student(int indexNumber, const std::string & name, const std::string & lastname, const std::tm & birthDate, const std::string & address = "default",
            const std::string & pesel = "default", Gender gender = Gender::Default, const std::string & fldOfStudy = "default");
                         
    Student(int && indexNumber, const std::string && name, const std::string && lastname, const std::tm && birthDate, const std::string && address = "default",
            const std::string && pesel = "default", Gender && gender = Gender::Default, const std::string && fldOfStudy = "default");
                    
    Student(const Student &other);

    Student& operator==(const Student & other);

    EntityType getEntityType(void) const override;
    std::string getFieldOfStudy(void) const override;
    void setFieldOfStudy(const std::string & fldOfStudy) override;

    std::string serialize(void) const override;

    void show(void) const override;
    void showExtented(void) const override;
    void modify(void) override;


    void showSubjects(void) const;
    bool addSubject(const std::string & subjectName);
    bool removeSubject(const std::string & subjectName);
    void showGrades(void) const;
    bool addGrade(const std::string & subject, float grade);
    bool removeGrade(const std::string & subject);
};