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

Professor::Professor(const Professor & other): Entity(other)
{
    this->m_academicTitle = other.m_academicTitle;
    this->m_department = other.m_department;
}

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
        this->m_academicTitle = other.m_academicTitle;
        this->m_department = other.m_department;
    }
    return *this;
}


AcademicTitle Professor::getAcademicTitle(void) const
{
    return m_academicTitle;
}

void Professor::setAcademicTitle(const AcademicTitle & title)
{
    m_academicTitle = title;
}

Department Professor::getDepartment(void) const
{
    return m_department;
}

void Professor::setDepartment(const Department & dep)
{
    m_department = dep;
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

std::string Professor::infoToString(void) const
{
    std::stringstream ssBirthday, ssEntityType, ssGender;

    ssBirthday << std::put_time(&m_birthDate, "%d.%m.%Yr");
    ssEntityType << this->getEntityType();
    ssGender << m_gender;
    std::string birthdate = ssBirthday.str();
    std::string entityType = ssEntityType.str();
    std::string gender = ssGender.str();

    return std::string("| ") + std::to_string(m_indexNumber) + " | " + entityType + " | " + m_name + " | " + m_lastname + " | " + birthdate + " | " 
              + m_address + " | " + m_pesel + " | " + gender + " | " + "N/A" + " | " + "N/A" + " | " + "N/A" + " | " 
              + academicTitleToString(m_academicTitle) + " | " + departmentToString(m_department) + "\n";
}

std::string Professor::extendedInfoToString(void) const
{
    std::stringstream ssGender;
    ssGender << m_gender;
    std::string gender = ssGender.str();
    return std::string("===================================================================================================================================================\n") +
           "Information about Professor:\n" +
           "Name: " + m_name + "\n" +
           "Last name: " + m_lastname + "\n" +
           "Address: " + m_address + "\n" +
           "Index number: " + std::to_string(m_indexNumber) + "\n" +
           "PESEL: " + m_pesel + "\n" +
           "Gender: " + gender + "\n" +
           "AcademicTitle: " + academicTitleToString(m_academicTitle) + "\n" +
           "Department: " + departmentToString(m_department) + "\n" +
           "===================================================================================================================================================\n" + 
           "===================================================================================================================================================\n"; 
}