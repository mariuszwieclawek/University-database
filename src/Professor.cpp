#include "Professor.hpp"
#include "EntityUtils.hpp"

Professor::Professor(int indexNumber, const std::string & name, const std::string & lastname, const std::tm & birthDate, const std::string & address,
                        const std::string & pesel, const Gender & gender, const AcademicTitle & acdtitle, const Department & dprtm):
    Entity(indexNumber, name, lastname, birthDate, address, pesel, gender),
    m_academicTitle(acdtitle),
    m_department(dprtm)
    {};

Professor::Professor(int && indexNumber, std::string && name, std::string && lastname, std::tm && birthDate, std::string && address,
                        std::string && pesel, Gender && gender, AcademicTitle && acdtitle, Department && dprtm):
    Entity(std::move(indexNumber), std::move(name), std::move(lastname), std::move(birthDate), std::move(address), std::move(pesel), std::move(gender)),
    m_academicTitle(std::move(acdtitle)),
    m_department(std::move(dprtm))
    {};

Professor::Professor(const Professor & other): Entity(other){};

Professor& Professor::operator==(const Professor & other)
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
    }
    return *this;
}

std::string Professor::serialize(void) const
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
                          m_pesel + "," + gender + "," + "N/A" + "," + "N/A" + "," + "N/A" + "," + academicTitleToString(m_academicTitle)
                          + "," + departmentToString(m_department) + "," + "\n";
    return ret_val;
}


EntityType Professor::getEntityType(void) const
{
    return EntityType::Professor;
}

void Professor::setFieldOfStudy(const std::string & fldOfStudy)
{
    /*TBD*/
}

void Professor::show(void) const
{
    std::stringstream ssBirthday;
    ssBirthday << std::put_time(&m_birthDate, "%d.%m.%Yr");
    std::string birthdate = ssBirthday.str();
    std::cout << "| " << m_indexNumber << " | " << this->getEntityType() << " | " << m_name << " | " << m_lastname << " | " << birthdate << " | " 
              << m_address << " | " << m_pesel << " | " << m_gender << " | " << "N/A" << " | " << "N/A" << " | " << "N/A" << " | " 
              << academicTitleToString(m_academicTitle) << " | " << departmentToString(m_department)<< std::endl;
}

void Professor::showExtented(void) const
{
    std::cout << "===================================================================================================================================================" << std::endl;
    std::cout << "Information about Professor:" << std::endl;
    std::cout << "Name: " << m_name << std::endl;
    std::cout << "Last name: " << m_lastname << std::endl;
    std::cout << "Address: " << m_address << std::endl;
    std::cout << "Index number: " << m_indexNumber << std::endl;
    std::cout << "PESEL: " << m_pesel << std::endl;
    std::cout << "Gender: " << m_gender << std::endl;
    std::cout << "===================================================================================================================================================" << std::endl;  
    std::cout << "===================================================================================================================================================" << std::endl;  
}

void Professor::modify(void)
{
    std::cout << "Actual data for Professor:" << std::endl;
    this->showExtented();
    std::cout << "Modification started. Please enter new values:" << std::endl;
    std::string input;

    std::cout << "Current Index number: " << m_indexNumber << std::endl << "Enter new Index number or skip(Enter): ";
    std::getline(std::cin, input);
    if (!input.empty()) m_indexNumber = std::stoi(input);

    std::cout << "Current Entity Type: " << this->getEntityType() << std::endl << "Enter new Entity Type or skip(Enter): ";
    std::getline(std::cin, input);
    // TBD
    // if (!input.empty()) m_name = input; 

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

    std::cout << "Current PESEL: " << m_pesel << std::endl << "Enter new PESEL or skip(Enter): ";
    std::getline(std::cin, input);
    if (!input.empty()) m_pesel = input;

    std::cout << "Current Gender: " << m_gender << std::endl << "Enter new Gender or skip(Enter): ";
    std::getline(std::cin, input);
    if (!input.empty()) m_gender = stringToGender(input);

    std::cout << "Current Academic Title: " << academicTitleToString(m_academicTitle) << std::endl << "Enter new Academic Title or skip(Enter): ";
    std::getline(std::cin, input);
    if (!input.empty()) m_academicTitle = stringToAcademicTitle(input);

    std::cout << "Current Department: " << departmentToString(m_department) << std::endl << "Enter new Department or skip(Enter): ";
    std::getline(std::cin, input);
    if (!input.empty()) m_department = stringToDepartment(input);
}