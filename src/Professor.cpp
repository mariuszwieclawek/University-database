#include "Professor.hpp"
#include "EntityUtils.hpp"
#include <format>

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
    std::ostringstream oss;
    oss << m_indexNumber << ","
        << this->getEntityType() << ","
        << m_name << ","
        << m_lastname << ","
        << std::put_time(&m_birthDate, "%d.%m.%Yr") << ","
        << m_address << ","
        << m_pesel << ","
        << m_gender << ","
        << "N/A" << ","
        << "N/A" << ","
        << "N/A" << ","
        << academicTitleToString(m_academicTitle) << ","
        << departmentToString(m_department) << "\n";
    return oss.str();
}

EntityType Professor::getEntityType(void) const
{
    return EntityType::Professor;
}

std::string Professor::infoToString(void) const
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
        << "N/A" << " | "
        << "N/A" << " | "
        << "N/A" << " | "
        << academicTitleToString(m_academicTitle) << " | "
        << departmentToString(m_department) << " | \n";

    return oss.str();
}

std::string Professor::extendedInfoToString(void) const
{
    std::ostringstream oss;

    oss << getPrintHeader()
        << "Information about Professor:\n"
        << "Name: " << m_name << "\n"
        << "Last name: " << m_lastname << "\n"
        << "Address: " << m_address << "\n"
        << "Index number: " << m_indexNumber << "\n"
        << "PESEL: " << m_pesel << "\n"
        << "Gender: " << m_gender << "\n"
        << "AcademicTitle: " << academicTitleToString(m_academicTitle) << "\n"
        << "Department: " << departmentToString(m_department) << "\n";

    return oss.str();
}

std::unique_ptr<Entity> Professor::clone(void) const
{
    return std::make_unique<Professor>(*this);
}