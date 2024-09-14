#include <sstream>
#include <stdexcept>
#include <iomanip>
#include "EntityUtils.hpp"


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

EntityType stringToEntityType(const std::string& str) 
{
    if (str == "Student") 
    {
        return EntityType::Student;
    } 
    else if (str == "Professor") 
    {
        return EntityType::Professor;
    } 
    else if (str == "Admin") 
    {
        return EntityType::Admin;
    }
    else if (str == "Staff") 
    {
        return EntityType::Staff;
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

    if (input == "Male") 
    {
        gender = Gender::Male;
    } 
    else if (input == "Female") 
    {
        gender = Gender::Female;
    } 
    else 
    {
        gender = Gender::Default;
    }

    return is;
}

std::ostream& operator<<(std::ostream & os, const EntityType & entity_type)
{
    switch (entity_type)
    {
    case EntityType::Student:
        os << "Student";
        break;
    case EntityType::Professor:
        os << "Professor";
        break;
    case EntityType::Admin:
        os << "Admin";
        break;
    case EntityType::Staff:
        os << "Staff";
        break;
    }
    return os;
}

std::istream& operator>>(std::istream& is, EntityType & entity_type)
{
    std::string input;
    is >> input;

    if (input == "Student") 
    {
        entity_type = EntityType::Student;
    } 
    else if (input == "Professor") 
    {
        entity_type = EntityType::Professor;
    }
    else if (input == "Admin") 
    {
        entity_type = EntityType::Admin;
    }
    else if (input == "Staff") 
    {
        entity_type = EntityType::Staff;
    }

    return is;
}