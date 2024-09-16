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
    std::string m_name;
    std::string m_lastname;
    std::tm m_birthDate;
    std::string m_address;
    int m_indexNumber;
    std::string m_pesel;
    Gender m_gender;
    std::string m_fieldOfStudy;
    std::set<std::string> m_subjects;
    /* 
    Grades is stored in convention as below 
    map<Subject , map<Comment, Grade> >   
         Comment - for which the student received a grade example: test, quiz, activity, oral answer...
    */
    std::map<std::string, std::map<std::string, float>> m_grades;
    
public:
    Student(void);
    Student(const std::string & name, const std::string & lastname, const std::tm & birthDate, const std::string & address = "default",
            int indexNumber = 0, const std::string & pesel = "default", Gender gender = Gender::Default, const std::string & fldOfStudy = "default");
                         
    Student(const std::string && name, const std::string && lastname, const std::tm && birthDate, const std::string && address = "default",
            int && indexNumber = 0, const std::string && pesel = "default", Gender && gender = Gender::Default, const std::string && fldOfStudy = "default");
                    
    Student(const Student &other);

    Student& operator==(const Student & other);

    std::string getName(void) const override;
    void setName(const std::string & name) override;
    std::string getLastname(void) const override;
    void setLastname(const std::string & lastname) override;
    std::string getPesel(void) const override;
    void setPesel(const std::string & pesel) override;
    int getIndex(void) const override;
    void setIndex(const int & index) override;
    EntityType getEntityType(void) const override;
    std::string getFieldOfStudy(void) const override;
    void setFieldOfStudy(const std::string & fldOfStudy) override;

    std::string serialize(void) const override;

    std::set<std::string> getMandatorySubjects(void) const override;

    void show(void) const override;
    void showExtented(void) const override;
    void modify(void) override;


    void showSubjects(void) const;
    bool addSubject(const std::string & subjectName);
    bool removeSubject(const std::string & subjectName);
    void showGrades(void) const;
    bool addGrade(const std::string & subject, const std::string & comment, float grade);
    bool removeGrade(const std::string & subject, const std::string & comment);
};