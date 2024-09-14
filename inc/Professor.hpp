#pragma once
#include "Entity.hpp"


class Professor : public Entity
{
private:
    std::string m_name;
    std::string m_lastname;
    std::tm m_birthDate;
    std::string m_address;
    int m_indexNumber;
    std::string m_pesel;
    Gender m_gender;
public:
    Professor(void);
    Professor(const std::string & name, const std::string & lastname, const std::tm & birthDate, const std::string & address = "default",
                         int indexNumber = 0, const std::string & pesel = "default", Gender gender = Gender::Default);
                         
    Professor(const std::string && name, const std::string && lastname, const std::tm && birthDate, const std::string && address = "default",
                         int indexNumber = 0, std::string && pesel = "default", Gender && gender = Gender::Default);
                    
    Professor(const Professor &other);

    Professor& operator==(const Professor & other);

    std::string getName(void) const override;
    void setName(const std::string & name) override;
    std::string getLastname(void) const override;
    void setLastname(const std::string & lastname) override;
    std::string getPesel(void) const override;
    void setPesel(const std::string & name) override;
    int getIndex(void) const override;
    void setIndex(const int & index) override;
    EntityType getEntityType(void) const override;

    std::string serialize(void) const override;

    std::set<std::string> getMandatorySubjects(void) const override;
    std::string getFieldOfStudy(void) const override;

    void show(void) const override;
    void showExtented(void) const override;
    void modify(void) override;

};