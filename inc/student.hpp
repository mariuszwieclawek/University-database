#pragma once
#include "Entity.hpp"
#include <string>
#include <set>
#include <map>
#include <vector>
#include <ctime>

#define MIN_GRADE 0
#define MAX_GRADE 6

enum class Gender {
    Male,
    Female,
    Default
};

Gender stringToGender(const std::string& str);
std::tm stringToTm(const std::string& dateStr, const std::string& format);
std::string TmToString(const std::tm & tmdate, const std::string& format);

std::ostream& operator<<(std::ostream & os, const Gender & gender);
std::istream& operator>>(std::istream & is, Gender & gender);

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
                         int indexNumber = 0, const std::string & pesel = "default", Gender gender = Gender::Default);
                         
    Student(const std::string && name, const std::string && lastname, const std::tm && birthDate, const std::string && address = "default",
                         int indexNumber = 0, std::string && pesel = "default", Gender && gender = Gender::Default);
                    
    Student(const Student &other);

    Student& operator==(const Student & other);

    std::string serialize(void) const override;
    std::string getName(void) const override;
    void setName(const std::string & name) override;
    std::string getLastname(void) const override;
    void setLastname(const std::string & lastname) override;
    std::string getPesel(void) const override;
    void setPesel(const std::string & name) override;
    int getIndex(void) const override;
    void setIndex(const int & index) override;
    std::set<std::string> getMandatorySubjects(void) const override;
    std::string getFieldOfStudy(void) const override;

    void show(void) const override;
    void showExtented(void) const override;
    
    void modify(void) override;

    void showSubjects(void) const override;
    bool addSubject(const std::string & subjectName) override;
    bool removeSubject(const std::string & subjectName) override;

    void showGrades(void) const override;
    bool addGrade(const std::string & subject, const std::string & comment, float grade) override;
    bool removeGrade(const std::string & subject, const std::string & comment) override;
};