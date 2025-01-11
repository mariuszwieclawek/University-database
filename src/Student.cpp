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

bool Student::modifyField(const std::string& fieldName, const FieldValue& newValue)
{
    // std::cout << "Actual data for student:" << std::endl;
    // this->extendedInfoToString();
    // std::cout << "Modification started. Please enter new values:" << std::endl;
    // std::string input;

    // std::cout << "Current Index number: " << m_indexNumber << std::endl << "Enter new Index number or skip(Enter): ";
    // std::getline(std::cin, input);
    // if (!input.empty()) m_indexNumber = std::stoi(input);

    // std::cout << "Current Entity Type: " << this->getEntityType() << std::endl << "Enter new Entity Type or skip(Enter): ";
    // std::getline(std::cin, input);
    // // TBD
    // // if (!input.empty()) m_name = input; 

    // std::cout << "Current Name: " << m_name << std::endl << "Enter new Name or skip(Enter): ";
    // std::getline(std::cin, input);
    // if (!input.empty()) m_name = input;

    // std::cout << "Current Last name: " << m_lastname << std::endl << "Enter new Last name or skip(Enter): ";
    // std::getline(std::cin, input);
    // if (!input.empty()) m_lastname = input;

    // std::cout << "Current birthday date: " << TmToString(m_birthDate, "%d.%m.%Y") << std::endl << "Enter new Birthday date or skip(Enter): ";
    // std::getline(std::cin, input);
    // if (!input.empty()) m_birthDate = stringToTm(input, "%d.%m.%Y");

    // std::cout << "Current Address: " << m_address << std::endl << "Enter new Address or skip(Enter): ";
    // std::getline(std::cin, input);
    // if (!input.empty()) m_address = input;

    // std::cout << "Current PESEL: " << m_pesel << std::endl << "Enter new PESEL or skip(Enter): ";
    // std::getline(std::cin, input);
    // if (!input.empty()) m_pesel = input;

    // std::cout << "Current Gender: " << m_gender << std::endl << "Enter new Gender or skip(Enter): ";
    // std::getline(std::cin, input);
    // if (!input.empty()) m_gender = stringToGender(input);

    // std::cout << "Current Field of Study: " << m_fieldOfStudy << std::endl << "Enter new Field of Study or skip(Enter): ";
    // std::getline(std::cin, input);
    // if (!input.empty()) m_fieldOfStudy = input;

    // std::cout << "Current Subjects: ";
    // this->showSubjects();
    // std::cout << "Enter new Subjects or skip(Enter): ";
    // std::getline(std::cin, input);
    // // if (!input.empty()) m_subjects = input;

    // std::cout << "Current Grades: ";
    // this->showGrades();
    // std::cout << "Enter new Grades or skip(Enter): ";
    // std::getline(std::cin, input);
    // if (!input.empty()) m_grades = input;

        bool ret_val = false;

    if (fieldName == "index") 
    {
        m_indexNumber = std::get<int>(newValue);
        ret_val = true;
    } 
    else if (fieldName == "name") 
    {
        m_name = std::get<std::string>(newValue);
        ret_val = true;
    } 
    else if (fieldName == "lastname") 
    {
        m_lastname = std::get<std::string>(newValue);
        ret_val = true;
    } 
    else if (fieldName == "birthdaydate") 
    {
        m_birthDate = std::get<std::tm>(newValue);
        ret_val = true;
    }
    else if (fieldName == "address") 
    {
        m_address = std::get<std::string>(newValue);
        ret_val = true;
    }
    else if (fieldName == "pesel") 
    {
        m_pesel = std::get<std::string>(newValue);
        ret_val = true;
    }
    else if (fieldName == "gender") 
    {
        m_gender = std::get<Gender>(newValue);
        ret_val = true;
    }
    else if (fieldName == "fieldofstudy") 
    {
        m_fieldOfStudy = std::get<std::string>(newValue);
        ret_val = true;
    }
    else if (fieldName == "subjects") 
    {
        m_subjects = std::get<std::set<std::string>>(newValue);
        ret_val = true;
    }
    else if (fieldName == "grades") 
    {
        m_grades = std::get<std::map<std::string, std::vector<float>>>(newValue);
        ret_val = true;
    }
    else 
    {
        ret_val = false;
    }

    return ret_val;
    
}

void Student::showSubjects(void) const
{
    std::cout << "===================================================================================================================================================" << std::endl;
    std::cout << "Subjects for student:" << std::endl;
    for(const auto & sb : m_subjects)
    {
        std::cout << "-" << sb << std::endl;
    }
    std::cout << "===================================================================================================================================================" << std::endl;
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
    std::cout << "===================================================================================================================================================" << std::endl;
    std::cout << "Grades of a " << m_name << " " << m_lastname << ":" << std::endl;
    for(const auto & [subject, grades] : m_grades)
    {
        std::cout << "\rSubject: \n\t" << subject << ":\n\t\t";
        for(const auto & grade : grades)
        {
            std::cout << grade << ",";
        }
    }
    std::cout << "\r===================================================================================================================================================" << std::endl;
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