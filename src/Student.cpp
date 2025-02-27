#include "Student.hpp"
#include "EntityUtils.hpp"
#include <string>
#include <iostream>

Student::Student(int indexNumber, const std::string & name, const std::string & lastname, const std::tm & birthDate, 
                    const std::string & address, const std::string & pesel, Gender gender, const std::string & fldOfStudy,
                    const std::string & subjects, const std::string & grades):
    Entity(indexNumber, name, lastname, birthDate, address, pesel, gender),
    m_fieldOfStudy(fldOfStudy),
    m_subjects(stringToSet(subjects)),
    m_grades(parseGrades(grades))
    {};

Student::Student(int && indexNumber, const std::string && name, const std::string && lastname, const std::tm && birthDate, 
                const std::string && address, const std::string && pesel, Gender && gender, const std::string && fldOfStudy,
                const std::string && subjects, const std::string && grades):
    Entity(std::move(indexNumber), std::move(name), std::move(lastname), std::move(birthDate), std::move(address), std::move(pesel), std::move(gender)),  
    m_fieldOfStudy(std::move(fldOfStudy)),
    m_subjects(std::move(stringToSet(subjects))),
    m_grades(std::move(parseGrades(grades)))
    {};

Student::Student(const Student & other): Entity(other), m_fieldOfStudy(other.m_fieldOfStudy){};

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

std::string Student::getFieldOfStudy(void) const
{
    return m_fieldOfStudy;
}

void Student::setFieldOfStudy(const std::string & fld_of_study)
{
    m_fieldOfStudy = fld_of_study;
}

std::set<std::string> Student::getSubjects(void) const
{
    return m_subjects;
}

void Student::setSubjects(const std::set<std::string> & subjects)
{
    m_subjects = subjects;
}

std::map<std::string, std::vector<float>> Student::getGrades(void) const
{
    return m_grades;
}

void Student::setGrades(const std::map<std::string, std::vector<float>> & grades)
{
    m_grades = grades;
}

std::string Student::serialize(void) const
{
    std::stringstream ssIndexNmb, ssEntityType, ssGender, ssBirthday;
    ssIndexNmb << m_indexNumber;
    ssEntityType << this->getEntityType();
    ssGender << m_gender;
    ssBirthday << std::put_time(&m_birthDate, "%d.%m.%Yr");
    std::string indexNumber = ssIndexNmb.str();
    std::string entityType = ssEntityType.str();
    std::string gender = ssGender.str();
    std::string birthdate = ssBirthday.str();
    std::string ret_val = indexNumber + "," + entityType + "," + m_name + "," + m_lastname + "," + birthdate + "," + m_address + "," +
                          m_pesel + "," + gender + "," + m_fieldOfStudy + "," + setToString(m_subjects) + "," + gradesToString(m_grades) + "," 
                          + "N/A" + "," + "N/A" + "," "\n";
    return ret_val;
}


EntityType Student::getEntityType(void) const
{
    return EntityType::Student;
}


std::string Student::infoToString(void) const
{
    std::stringstream ssBirthday, ssEntityType, ssGender;

    ssBirthday << std::put_time(&m_birthDate, "%d.%m.%Yr");
    ssEntityType << this->getEntityType();
    ssGender << m_gender;
    std::string birthdate = ssBirthday.str();
    std::string entityType = ssEntityType.str();   
    std::string gender = ssGender.str();

    return std::string("| ") + std::to_string(m_indexNumber) + " | " + entityType + " | " + m_name + " | " + m_lastname + " | " + birthdate + " | " 
    + m_address + " | " + m_pesel + " | " + gender + " | " + m_fieldOfStudy + " | " + setToString(m_subjects) + " | " + gradesToString(m_grades) + " |" + "\n";
}

std::string Student::extendedInfoToString(void) const
{
    std::stringstream ssGender;
    ssGender << m_gender;
    std::string gender = ssGender.str();
    return  std::string("===================================================================================================================================================\n") +
            "Information about student:\n" +
            "Name: " + m_name + "\n" +
            "Last name: " + m_lastname + "\n" +
            "Address: " + m_address + "\n" +
            "Index number: " + std::to_string(m_indexNumber) + "\n" +
            "PESEL: " + m_pesel + "\n" +
            "Gender: " + gender + "\n" +
            "===================================================================================================================================================\n" +
    // this->showSubjects();
    // this->showGrades();
            "===================================================================================================================================================\n"; 
}


std::unique_ptr<Entity> Student::clone() const 
{
    return std::make_unique<Student>(*this);
}

std::string Student::showSubjects(void) const 
{
    std::ostringstream oss;
    oss << "===================================================================================================================================================" << std::endl;
    oss << "Subjects for student:" << std::endl;
    for (const auto& sb : m_subjects) {
        oss << "-" << sb << std::endl;
    }
    oss << "===================================================================================================================================================" << std::endl;
    return oss.str();
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

std::string Student::showGrades(void) const
{
    std::ostringstream oss;
    oss << "===================================================================================================================================================" << std::endl;
    oss << "Grades of a " << m_name << " " << m_lastname << ":" << std::endl;
    for(const auto & [subject, grades] : m_grades)
    {
        oss << "\rSubject: \n\t" << subject << ":\n\t\t";
        for(const auto & grade : grades)
        {
            oss << grade << ",";
        }
    }
    oss << "\r===================================================================================================================================================" << std::endl;
    
    return oss.str();
}

bool Student::addGrade(const std::string & subject, float grade)
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

    m_grades[subject].push_back(grade);

    return true;
}
    
bool Student::removeGrade(const std::string & subject)
{
    if( bool subjectIsAdded = m_subjects.contains(subject); false == subjectIsAdded )
    {
        std::cerr << "\t[ERROR]\t" + std::string(__func__) + " function failed" << std::endl;
        return false;
    }

    m_grades[subject].clear();

    return true;
}