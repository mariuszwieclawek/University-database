#include "Student.hpp"
#include "EntityUtils.hpp"
#include <string>
#include <iostream>

Student::Student(int indexNumber, const std::string & name, const std::string & lastname, const std::tm & birthDate, 
                    const std::string & address, const std::string & pesel, Gender gender, const FieldOfStudy & fldOfStudy,
                    const subjects_t & subjects, const gradesToSubject_t & grades):
    Entity(indexNumber, name, lastname, birthDate, address, pesel, gender),
    m_fieldOfStudy(fldOfStudy),
    m_subjects(subjects),
    m_grades(grades)
    {};

Student::Student(int && indexNumber, const std::string && name, const std::string && lastname, const std::tm && birthDate, 
                const std::string && address, const std::string && pesel, Gender && gender, const FieldOfStudy && fldOfStudy,
                const subjects_t && subjects, const gradesToSubject_t && grades):
    Entity(std::move(indexNumber), std::move(name), std::move(lastname), std::move(birthDate), std::move(address), std::move(pesel), std::move(gender)),  
    m_fieldOfStudy(std::move(fldOfStudy)),
    m_subjects(std::move(subjects)),
    m_grades(std::move(grades))
    {};

Student::Student(const Student & other): Entity(other)
{
    this->m_fieldOfStudy = other.m_fieldOfStudy;
    this->m_subjects =  other.m_subjects;
    this->m_grades =  other.m_grades;
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
        this->m_fieldOfStudy = other.m_fieldOfStudy;
        this->m_subjects = other.m_subjects;
        this->m_grades = other.m_grades;
    }
    return *this;
}

FieldOfStudy Student::getFieldOfStudy(void) const
{
    return m_fieldOfStudy;
}

void Student::setFieldOfStudy(const FieldOfStudy & fld_of_study)
{
    m_fieldOfStudy = fld_of_study;
}

subjects_t Student::getSubjects(void) const
{
    return m_subjects;
}

void Student::setSubjects(const subjects_t & subjects)
{
    m_subjects = subjects;
}

gradesToSubject_t Student::getGrades(void) const
{
    return m_grades;
}

void Student::setGrades(const gradesToSubject_t & grades)
{
    m_grades = grades;
}

std::string Student::serialize(void) const
{
    std::ostringstream oss;

    oss << m_indexNumber << ","
        << this->getEntityType() << ","
        << m_name << ","
        << m_lastname << ","
        << std::put_time(&m_birthDate, "%d.%m.%Yr") << ","
        << m_address << ","
        << m_pesel << ","
        << m_gender << ","
        << fieldOfStudyToString(m_fieldOfStudy) << ","
        << subjectsToString(m_subjects) << ","
        << gradesToString(m_grades) << ","
        << "N/A" << ","
        << "N/A" << ","
        << "\n";

    return oss.str();
}


EntityType Student::getEntityType(void) const
{
    return EntityType::Student;
}


std::string Student::infoToString(void) const
{
    std::ostringstream oss;

    oss << "| " << m_indexNumber << " | "
        << this->getEntityType() << " | "
        << m_name << " | "
        << m_lastname << " | "
        << std::put_time(&m_birthDate, "%d.%m.%Yr") << " | "
        << m_address << " | "
        << m_pesel << " | "
        << m_gender << " | "
        << fieldOfStudyToString(m_fieldOfStudy) << " | "
        << subjectsToString(m_subjects) << " | "
        << gradesToString(m_grades) << " |"
        << "\n";

    return oss.str();
}

std::string Student::extendedInfoToString(void) const
{
    std::ostringstream oss;

    oss << getPrintHeader()
        << "Information about student:\n"
        << "Name: " << m_name << "\n"
        << "Last name: " << m_lastname << "\n"
        << "Address: " << m_address << "\n"
        << "Index number: " << m_indexNumber << "\n"
        << "PESEL: " << m_pesel << "\n"
        << "Gender: " << m_gender << "\n"
        << this->showSubjects()
        << this->showGrades();

    return oss.str();
}

std::unique_ptr<Entity> Student::clone(void) const
{
    return std::make_unique<Student>(*this);
}

std::string Student::showSubjects(void) const 
{
    std::ostringstream oss;
    oss << getPrintHeader();
    oss << "Subjects for student:" << std::endl;
    for (const auto& sb : m_subjects) {
        oss << "-" << subjectToString(sb) << std::endl;
    }
    oss << getPrintHeader();
    return oss.str();
}

std::string Student::showGrades(void) const
{
    std::ostringstream oss;
    oss << getPrintHeader();
    oss << "Grades of a " << m_name << " " << m_lastname << ":" << std::endl;
    for(const auto & [subject, grades] : m_grades)
    {
        oss << "\rSubject: \n\t" << subjectToString(subject) << ":\n\t\t";
        for(const auto & grade : grades)
        {
            oss << grade << ",";
        }
        oss << "\n";
    }
    oss << getPrintHeader();
    
    return oss.str();
}

bool Student::addSubject(const Subject & subjectName)
{
    auto isSubjectInserted = m_subjects.insert(subjectName); 

    return isSubjectInserted.second;
}

bool Student::removeSubject(const Subject & subjectName)
{
    auto it = m_subjects.find(subjectName);

    if (it != m_subjects.end())
    {
        m_subjects.erase(it);
        return true;
    }

    return false;
}

bool Student::addGrade(const Subject& subject, float grade)
{
    if (grade < MIN_GRADE || grade > MAX_GRADE) return false;

    if (m_subjects.find(subject) == m_subjects.end()) return false; // Sprawdzamy, czy przedmiot istnieje

    m_grades[subject].push_back(grade); // Dodajemy ocenę do mapy

    return true;
}

bool Student::removeGrade(const Subject& subject)
{
    if (m_subjects.find(subject) == m_subjects.end()) return false; // Sprawdzamy, czy przedmiot istnieje

    m_grades[subject].clear(); // Czyścimy listę ocen dla danego przedmiotu

    return true;
}