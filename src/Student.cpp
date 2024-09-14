#include "Student.hpp"
#include <iostream>
#include <sstream>
#include <ctime>
#include <iomanip>


static const std::set<std::string> mandatorySubjects = {"Math", "Physics", "Analysis", "Statistics"};


Gender stringToGender(const std::string& str) 
{
    if (str == "Male") 
    {
        return Gender::Male;
    } 
    else if (str == "Female") 
    {
        return Gender::Female;
    } 
    else if (str == "Default") 
    {
        return Gender::Default;
    } 
    else 
    {
        throw std::runtime_error(std::string(__func__) + " function failed");
    }
}

std::tm stringToTm(const std::string& dateStr, const std::string& format) 
{
    std::tm tm = {};
    std::istringstream ss(dateStr);
    ss >> std::get_time(&tm, format.c_str());
    
    if (ss.fail())
    {
        throw std::runtime_error(std::string(__func__) + " function failed");
    }
    
    return tm;
}

std::string TmToString(const std::tm & tmdate, const std::string& format) 
{
    std::stringstream ssBirthday;
    ssBirthday << std::put_time(&tmdate, format.c_str());
    std::string birthdate = ssBirthday.str();
    
    return birthdate;
}

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

std::istream& operator>>(std::istream& is, Gender& gender)
{
    std::string input;
    is >> input;

    if (input == "Male") {
        gender = Gender::Male;
    } else if (input == "Female") {
        gender = Gender::Female;
    } else {
        gender = Gender::Default;
    }

    return is;
}


Student::Student(void)
{
    m_subjects.insert(mandatorySubjects.begin(), mandatorySubjects.end());
};

Student::Student(const std::string & name, const std::string & lastname, const std::tm & birthDate, const std::string & address,
                         int indexNumber, const std::string & pesel, Gender gender) : 
    m_name(name), 
    m_lastname(lastname),
    m_birthDate(birthDate),
    m_address(address),
    m_indexNumber(indexNumber),
    m_pesel(pesel),
    m_gender(gender)
    {
        m_subjects.insert(mandatorySubjects.begin(), mandatorySubjects.end());
    };

Student::Student(const std::string && name, const std::string && lastname, const std::tm && birthDate, const std::string && address,
                         int indexNumber, std::string && pesel, Gender && gender) :  
    m_name(std::move(name)), 
    m_lastname(std::move(lastname)),
    m_birthDate(std::move(birthDate)),
    m_address(std::move(address)),
    m_indexNumber(indexNumber),
    m_pesel(std::move(pesel)),
    m_gender(std::move(gender))
    {
        m_subjects.insert(mandatorySubjects.begin(), mandatorySubjects.end());
    };

Student::Student(const Student & other)
{
    if(this != &other)
    {
        m_name = other.m_name;
        m_lastname = other.m_lastname;
        m_birthDate = other.m_birthDate;
        m_address = other.m_address;
        m_indexNumber = other.m_indexNumber;
        m_pesel = other.m_pesel;
        m_gender = other.m_gender;
        m_subjects = other.m_subjects;
        m_grades = other.m_grades;
    }
}

Student& Student::operator==(const Student & other)
{
    if(this != &other)
    {
        this->m_name = other.m_name; 
        this->m_lastname = other.m_lastname;
        this->m_birthDate = other.m_birthDate;
        this->m_address = other.m_address;
        this->m_indexNumber = other.m_indexNumber;
        this->m_pesel = other.m_pesel;
        this->m_gender = other.m_gender;
        this->m_subjects = other.m_subjects;
        this->m_grades = other.m_grades;
    }
    return *this;
}

std::string Student::serialize(void) const
{
    std::stringstream ssIndexNmb, ssGender, ssBirthday;
    ssIndexNmb << m_indexNumber;
    ssGender << m_gender;
    ssBirthday << std::put_time(&m_birthDate, "%d.%m.%Yr");
    std::string indexNumber = ssIndexNmb.str();
    std::string gender = ssGender.str();
    std::string birthdate = ssBirthday.str();
    std::string ret_val = m_name + "," + m_lastname + "," + birthdate + "," + m_address + "," + indexNumber + "," +
                          m_pesel + "," + gender + "\n";
    return ret_val;
}

std::string Student::getName(void) const
{
    return m_name;
}

void Student::setName(const std::string & name)
{
    m_name = name;
}

std::string Student::getLastname(void) const
{
    return m_lastname;
}

void Student::setLastname(const std::string & lastname)
{
    m_lastname = lastname;
}

std::string Student::getPesel(void) const
{
    return m_pesel;
}

void Student::setPesel(const std::string & pesel)
{
    m_pesel = pesel;
}

int Student::getIndex(void) const
{
    return m_indexNumber;
}
void Student::setIndex(const int & index)
{
    m_indexNumber = index;
}

std::set<std::string> Student::getMandatorySubjects(void) const
{
    return mandatorySubjects;
}

std::string Student::getFieldOfStudy(void) const
{
    return "Mathematics";
}


void Student::show(void) const
{
    
    std::stringstream ssBirthday;
    ssBirthday << std::put_time(&m_birthDate, "%d.%m.%Yr");
    std::string birthdate = ssBirthday.str();
    std::cout << m_name << " | " << m_lastname << " | " << birthdate << " | " << m_address << " | " 
              << m_indexNumber << " | " << m_pesel << " | " << m_gender << std::endl;
}

void Student::showExtented(void) const
{
    std::cout << "==========================================================" << std::endl;
    std::cout << "Information about student:" << std::endl;
    std::cout << "Name: " << m_name << std::endl;
    std::cout << "Last name: " << m_lastname << std::endl;
    std::cout << "Address: " << m_address << std::endl;
    std::cout << "Index number: " << m_indexNumber << std::endl;
    std::cout << "PESEL: " << m_pesel << std::endl;
    std::cout << "Gender: " << m_gender << std::endl;
    std::cout << "==========================================================" << std::endl;  
    this->showSubjects();
    this->showGrades();
    std::cout << "==========================================================" << std::endl;  
}

void Student::modify(void)
{
    std::cout << "Actual data for student:" << std::endl;
    this->showExtented();
    std::cout << "Modification started. Please enter new values:" << std::endl;
    std::string input;

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Current Name: " << m_name << std::endl << "Enter new Name or skip(Enter): ";
    std::getline(std::cin, input);
    if (!input.empty()) m_name = input;

    std::cout << "Current Last name: " << m_lastname << std::endl << "Enter new Last name or skip(Enter): ";
    std::getline(std::cin, input);
    if (!input.empty()) m_lastname = input;

    std::cout << "Current birthday date: " << TmToString(m_birthDate, "%d.%m.%Y") << std::endl << "Enter new Birthday date or skip(Enter): ";
    std::getline(std::cin, input);
    if (!input.empty()) m_birthDate = stringToTm(input, "%d.%m.%Y");

    std::cout << "Current Address: " << m_address << std::endl << "Enter new Address or skip(Enter): ";
    std::getline(std::cin, input);
    if (!input.empty()) m_address = input;

    std::cout << "Current Index number: " << m_indexNumber << std::endl << "Enter new Index number or skip(Enter): ";
    std::getline(std::cin, input);
    if (!input.empty()) m_indexNumber = std::stoi(input);

    std::cout << "Current PESEL: " << m_pesel << std::endl << "Enter new PESEL or skip(Enter): ";
    std::getline(std::cin, input);
    if (!input.empty()) m_pesel = input;

    std::cout << "Current gender: " << m_gender << std::endl << "Enter new Gender or skip(Enter): ";
    std::getline(std::cin, input);
    if (!input.empty()) m_gender = stringToGender(input);
    
}

void Student::showSubjects(void) const
{
    std::cout << "==========================================================" << std::endl;
    std::cout << "Subjects for student:" << std::endl;
    for(const auto & sb : m_subjects)
    {
        std::cout << "-" << sb << std::endl;
    }
    std::cout << "==========================================================" << std::endl;
}

bool Student::addSubject(const std::string & subjectName)
{
    auto isSubjectInserted = m_subjects.insert(subjectName); 
    if( false == isSubjectInserted.second)
    {
        std::cerr << "\t[ERROR]\t" + std::string(__func__) + " function failed" << std::endl;
    }
    return isSubjectInserted.second;
}

bool Student::removeSubject(const std::string & subjectName)
{
    bool isExist = m_subjects.contains(subjectName);
    if( true == isExist)
    {
        m_subjects.erase(subjectName);
    }
    else
    {
        std::cerr << "\t[ERROR]\t" + std::string(__func__) + " function failed" << std::endl;
    }
    return isExist;
}

void Student::showGrades(void) const
{
    std::cout << "==========================================================" << std::endl;
    std::cout << "Grades of a " << m_name << " " << m_lastname << ":" << std::endl;
    for(const auto & [subject, commentAndGrade] : m_grades)
    {
        std::cout << "\rSubject: \n\t" << subject << ":\n\t\t";
        for(const auto & [comment, grade] : commentAndGrade)
        {
            std::cout << "* " << grade << "\t(Note:" << comment << ")\n\t\t";
        }
    }
    std::cout << "\r==========================================================" << std::endl;
}

bool Student::addGrade(const std::string & subject, const std::string & comment, float grade)
{
    if( (grade < MIN_GRADE) && (grade > MAX_GRADE) )
    {
        std::cerr << "\t[ERROR]\t" + std::string(__func__) + " function failed" << std::endl;
        return false;
    }

    if( bool subjectIsAdded = m_subjects.contains(subject); false == subjectIsAdded )
    {
        std::cerr << "\t[ERROR]\t" + std::string(__func__) + " function failed" << std::endl;
        return false;
    }

    if( bool commentIsAdded = m_grades[subject].contains(comment); false == commentIsAdded )
    {
        m_grades[subject][comment] = grade;
    }
    else
    {
        std::cerr << "\t[ERROR]\t" + std::string(__func__) + " function failed" << std::endl;
        return false;
    }

    return true;
}
    
bool Student::removeGrade(const std::string & subject, const std::string & comment)
{
    if( bool subjectIsAdded = m_subjects.contains(subject); false == subjectIsAdded )
    {
        std::cerr << "\t[ERROR]\t" + std::string(__func__) + " function failed" << std::endl;
        return false;
    }

    if( bool commentIsAdded = m_grades[subject].contains(comment); true == commentIsAdded )
    {
        m_grades[subject].erase(comment);
    }
    else
    {
        std::cerr << "\t[ERROR]\t" + std::string(__func__) + " function failed" << std::endl;
        return false;
    }

    return true;
}