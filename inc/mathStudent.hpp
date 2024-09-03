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

Gender stringToGender(const std::string& str);

std::ostream& operator<<(std::ostream & os, const Gender & gender);
std::istream& operator>>(std::istream & is, Gender & gender);

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

    MathStudent& operator==(const MathStudent & other);

    std::vector<std::string> getStudent(void) const override;
    std::string getName(void) const override;
    void setName(const std::string & name) override;
    std::string getLastname(void) const override;
    void getLastname(const std::string & lastname) override;
    std::string getPesel(void) const override;
    void setPesel(const std::string & name) override;
    std::string getFieldOfStudy(void) const override;

    void showStudent(void) const override;
    void showStudentEx(void) const override;
    
    void modifyStudent(void) override;

    void showSubjects(void) const override;
    bool addSubject(const std::string & subjectName) override;
    bool removeSubject(const std::string & subjectName) override;

    void showGrades(void) const override;
    bool addGrade(const std::string & subject, const std::string & comment, float grade) override;
    bool removeGrade(const std::string & subject, const std::string & comment) override;
};