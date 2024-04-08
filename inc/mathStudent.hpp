#pragma once
#include "student.hpp"
#include <string>
#include <set>
#include <map>
#include <vector>

#define MIN_GRADE 0
#define MAX_GRADE 6

enum class Gender {
    Male,
    Female,
    Default
};

class MathStudent : public Student
{
private:
    std::string m_name;
    std::string m_lastname;
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
    MathStudent(void);
    MathStudent(const std::string & name, const std::string & lastname, const std::string & address = "default",
                         int indexNumber = 0, const std::string & pesel = "default", Gender gender = Gender::Default);
                         
    MathStudent(const std::string && name, const std::string && lastname, const std::string && address = "default",
                         int indexNumber = 0, std::string && pesel = "default", Gender && gender = Gender::Default);

    std::string getName(void) const;
    void setName(const std::string & name);

    void showStudent(void) const;

    void showSubjects(void) const;
    bool addSubject(const std::string & subjectName);
    bool removeSubject(const std::string & subjectName);

    void showGrades(void) const;
    bool addGrade(const std::string & subject, const std::string & comment, float grade);
    bool removeGrade(const std::string & subject, const std::string & comment);
};