#pragma once
#include <iomanip>
#include <map>
#include <set>
#include <vector>
#include <memory>
#include "Enums.hpp"

class Entity
{
public:
    Entity(int indexNumber, const std::string & name, const std::string & lastname, const std::tm & birthDate, 
            const std::string & address = "default", const std::string & pesel = "default", Gender gender = Gender::Default);
    Entity(int && indexNumber, const std::string && name, const std::string && lastname, const std::tm && birthDate, 
            const std::string && address = "default", const std::string && pesel = "default", Gender && gender = Gender::Default);
    Entity(const Entity & other);

    int getIndex(void) const;
    void setIndex(const int & index);
    std::string getName(void) const;
    void setName(const std::string & name);
    std::string getLastname(void) const;
    void setLastname(const std::string & lastname);
    std::tm getBirthdayDate(void) const;
    void setBirthdayDate(const std::tm & birthdaydate);
    std::string getAddress(void) const;
    void setAddress(const std::string & addres);
    std::string getPesel(void) const;
    void setPesel(const std::string & pesel);
    Gender getGender(void) const;
    void setGender(const Gender & gender);

    virtual EntityType getEntityType() const = 0;

    virtual std::string serialize(void) const = 0;

    virtual std::string infoToString(void) const = 0;
    virtual std::string extendedInfoToString(void) const = 0;

    virtual std::unique_ptr<Entity> clone() const = 0;

protected:
    int m_indexNumber;
    std::string m_name;
    std::string m_lastname;
    std::tm m_birthDate;
    std::string m_address;
    std::string m_pesel;
    Gender m_gender;
};