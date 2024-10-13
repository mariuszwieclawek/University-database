#include <iostream>
#include "Entity.hpp"


Entity::Entity(int indexNumber, const std::string & name, const std::string & lastname, 
                const std::tm & birthDate, const std::string & address, const std::string & pesel, Gender gender): 
    m_indexNumber(indexNumber),
    m_name(name), 
    m_lastname(lastname),
    m_birthDate(birthDate),
    m_address(address),
    m_pesel(pesel),
    m_gender(gender)
    {};

Entity::Entity(int && indexNumber, const std::string && name, const std::string && lastname, const std::tm && birthDate, 
                const std::string && address, const std::string && pesel, Gender && gender):
    m_indexNumber(std::move(indexNumber)),
    m_name(std::move(name)), 
    m_lastname(std::move(lastname)),
    m_birthDate(std::move(birthDate)),
    m_address(std::move(address)),
    m_pesel(std::move(pesel)),
    m_gender(std::move(gender))
    {};

Entity::Entity(const Entity & other)
{
    if(this != &other)
    {
        m_indexNumber = other.m_indexNumber;
        m_name = other.m_name;
        m_lastname = other.m_lastname;
        m_birthDate = other.m_birthDate;
        m_address = other.m_address;
        m_pesel = other.m_pesel;
        m_gender = other.m_gender;
    }
}

int Entity::getIndex(void) const
{
    return m_indexNumber;
}
void Entity::setIndex(const int & index)
{
    m_indexNumber = index;
}

std::string Entity::getName(void) const
{
    return m_name;
}

void Entity::setName(const std::string & name)
{
    m_name = name;
}

std::string Entity::getLastname(void) const
{
    return m_lastname;
}

void Entity::setLastname(const std::string & lastname)
{
    m_lastname = lastname;
}

std::tm Entity::getBirthdayDate(void) const
{
    return m_birthDate;
}

void Entity::setBirthdayDate(const std::tm & birthdaydate)
{
    m_birthDate = birthdaydate;
}

std::string Entity::getAddress(void) const
{
    return m_address;
}

void Entity::setAddress(const std::string & addres)
{
    m_address = addres;
}

std::string Entity::getPesel(void) const
{
    return m_pesel;
}

void Entity::setPesel(const std::string & pesel)
{
    m_pesel = pesel;
}

Gender Entity::getGender(void) const
{
    return m_gender;
}

void Entity::setGender(const Gender & gender)
{
    m_gender = gender;
}


