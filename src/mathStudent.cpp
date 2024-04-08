#include "mathStudent.hpp"
#include <iostream>


static const std::set<std::string> initSubjects = {"Math", "Physics", "Analysis", "Statistics"};

std::ostream& operator<<(std::ostream & os, const Gender & gender)
{
    switch (gender)
    {
    case Gender::Male:
        os << "Male";
        break;
    case Gender::Female:
        os << "Female";
        break;
    default:
        os << "Default";
        break;
    }
    return os;
}


MathStudent::MathStudent(void)
{
    std::cout << "Konstruktor bez argumentow" << std::endl;
    m_subjects.insert(initSubjects.begin(), initSubjects.end());
};

MathStudent::MathStudent(const std::string & name, const std::string & lastname, const std::string & address,
                         int indexNumber, const std::string & pesel, Gender gender) : 
    m_name(name), 
    m_lastname(lastname),
    m_address(address),
    m_indexNumber(indexNumber),
    m_pesel(pesel),
    m_gender(gender)
    {
        std::cout << "Konstruktor kopiujacy argumenty" << std::endl;
        m_subjects.insert(initSubjects.begin(), initSubjects.end());
    };

MathStudent::MathStudent(const std::string && name, const std::string && lastname, const std::string && address,
                         int indexNumber, std::string && pesel, Gender && gender) :  
    m_name(std::move(name)), 
    m_lastname(std::move(lastname)),
    m_address(std::move(address)),
    m_indexNumber(indexNumber),
    m_pesel(std::move(pesel)),
    m_gender(std::move(gender))
    {
        std::cout << "Konstruktor przenoszacy argumenty" << std::endl;
        m_subjects.insert(initSubjects.begin(), initSubjects.end());
    };

std::string MathStudent::getName(void) const
{
    return m_name;
}

void MathStudent::setName(const std::string & name)
{
    m_name = name;
}

void MathStudent::showStudent(void) const
{
    std::cout << "==========================================================\n";
    std::cout << "Information about student:\n";
    std::cout << "Name: " << m_name << std::endl;
    std::cout << "Last name: " << m_lastname << std::endl;
    std::cout << "Address: " << m_address << std::endl;
    std::cout << "Index number: " << m_indexNumber << std::endl;
    std::cout << "PESEL: " << m_pesel << std::endl;
    std::cout << "Sex: " << m_gender << std::endl;
    std::cout << "==========================================================\n";  
    this->showSubjects();
    this->showGrades();
    std::cout << "==========================================================\n";  
}

void MathStudent::showSubjects(void) const
{
    std::cout << "==========================================================\n";
    std::cout << "Subjects for student:\n";
    for(const auto & sb : m_subjects)
    {
        std::cout << "-" << sb << std::endl;
    }
    std::cout << "==========================================================\n";
}

bool MathStudent::addSubject(const std::string & subjectName)
{
    auto isSubjectInserted = m_subjects.insert(subjectName); 
    if( false == isSubjectInserted.second)
    {
        std::cerr << "\t[ERROR]\t{addSubject} - insert failed" << std::endl;
    }
    return isSubjectInserted.second;
}

bool MathStudent::removeSubject(const std::string & subjectName)
{
    bool isExist = m_subjects.contains(subjectName);
    if( true == isExist)
    {
        m_subjects.erase(subjectName);
    }
    else
    {
        std::cerr << "\t[ERROR]\t{removeSubject} - Subject is not exist" << std::endl;
    }
    return isExist;
}

void MathStudent::showGrades(void) const
{
    std::cout << "==========================================================\n";
    std::cout << "Grades of a " << m_name << " " << m_lastname << ":\n";
    for(const auto & [subject, commentAndGrade] : m_grades)
    {
        std::cout << "\rSubject: \n\t" << subject << ":\n\t\t";
        for(const auto & [comment, grade] : commentAndGrade)
        {
            std::cout << "* " << grade << "\t(Note:" << comment << ")\n\t\t";
        }
    }
    std::cout << "\r==========================================================\n";
}

bool MathStudent::addGrade(const std::string & subject, const std::string & comment, float grade)
{
    if( (grade < MIN_GRADE) && (grade > MAX_GRADE) )
    {
        std::cerr << "\t[ERROR]\t{addGrade} - Invalid grade" << std::endl; 
        return false;
    }

    if( bool subjectIsAdded = m_subjects.contains(subject); false == subjectIsAdded )
    {
        std::cerr << "\t[ERROR]\t{addGrade} - Subject is not exist" << std::endl;
        return false;
    }

    if( bool commentIsAdded = m_grades[subject].contains(comment); false == commentIsAdded )
    {
        m_grades[subject][comment] = grade;
    }
    else
    {
        std::cerr << "\t[ERROR]\t{addGrade} - Grade for this comment is already added" << std::endl;
        return false;
    }

    return true;
}
    
bool MathStudent::removeGrade(const std::string & subject, const std::string & comment)
{
    if( bool subjectIsAdded = m_subjects.contains(subject); false == subjectIsAdded )
    {
        std::cerr << "\t[ERROR]\t{removeGrade} - Subject is not exist" << std::endl;
        return false;
    }

    if( bool commentIsAdded = m_grades[subject].contains(comment); true == commentIsAdded )
    {
        m_grades[subject].erase(comment);
    }
    else
    {
        std::cerr << "\t[ERROR]\t{removeGrade} - Grade for this comment is not exist" << std::endl;
        return false;
    }

    return true;
}