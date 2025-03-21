#pragma once
#include "Entity.hpp"
#include <set>
#include <map>
#include <vector>

#define MIN_GRADE 0
#define MAX_GRADE 6

using subjects_t = std::set<Subject>;
using grades_t = std::vector<float>;
using gradesToSubject_t = std::map<Subject, grades_t>;

class Student : public Entity
{
private:
    FieldOfStudy m_fieldOfStudy;
    subjects_t m_subjects;
    gradesToSubject_t m_grades;
    
public:
    Student(int indexNumber, const std::string & name, const std::string & lastname, const std::tm & birthDate, const std::string & address = "default",
            const std::string & pesel = "default", Gender gender = Gender::Default, const FieldOfStudy & fldOfStudy = FieldOfStudy::Default,
            const subjects_t & subjects = subjects_t(), const gradesToSubject_t & grades = gradesToSubject_t());
                         
    Student(int && indexNumber, const std::string && name, const std::string && lastname, const std::tm && birthDate, const std::string && address = "default",
            const std::string && pesel = "default", Gender && gender = Gender::Default, const FieldOfStudy && fldOfStudy = FieldOfStudy::Default,
            const subjects_t && subjects = subjects_t(), const gradesToSubject_t && grades = gradesToSubject_t());
                    
    Student(const Student &other);

    Student& operator==(const Student & other);

    FieldOfStudy getFieldOfStudy(void) const;
    void setFieldOfStudy(const FieldOfStudy & fld_of_study);
    subjects_t getSubjects(void) const;
    void setSubjects(const subjects_t & subjects);
    gradesToSubject_t getGrades(void) const;
    void setGrades(const gradesToSubject_t & grades);

    EntityType getEntityType(void) const override;

    std::string serialize(void) const override;
    std::string infoToString(void) const override;
    std::string extendedInfoToString(void) const override;

    std::unique_ptr<Entity> clone(void) const override;

    std::string showSubjects(void) const;
    std::string showGrades(void) const;

    bool addSubject(const Subject & subjectName);
    bool removeSubject(const Subject & subjectName);
    bool addGrade(const Subject& subject, float grade);
    bool removeGrade(const Subject & subject);
};