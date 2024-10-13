#pragma once
#include "Entity.hpp"
#include <map>

enum class AcademicTitle 
{
    AssociateProfessor,
    Professor,
    TitularProfessor,
    DoctorHabilitatus,
};


enum class Department
{
    ComputerScience,
    ElectronicsAndTelecommunications,
    Architecture,
    Mathematics,
    Physics,
    Chemistry,
    Medicine,
    Pharmacy,
    Psychology,
};



class Professor : public Entity
{
private:
    AcademicTitle m_academicTitle;
    Department m_department;
    std::tm m_hireDate;
public:
    Professor(int indexNumber, const std::string & name, const std::string & lastname, const std::tm & birthDate, const std::string & address = "default",
                const std::string & pesel = "default", const Gender & gender = Gender::Default, const AcademicTitle & acdtitle = AcademicTitle::DoctorHabilitatus,
                const Department & dprtm = Department::Mathematics, const std::tm & hireDate = {0});
                         
    Professor(int && indexNumber, std::string && name, std::string && lastname, std::tm && birthDate, std::string && address = "default",
                std::string && pesel = "default", Gender && gender = Gender::Default, AcademicTitle && acdtitle = AcademicTitle::DoctorHabilitatus,
                Department && dprtm = Department::Mathematics, std::tm && hireDate = {0});
                    
    Professor(const Professor &other);

    Professor& operator==(const Professor & other);

    EntityType getEntityType(void) const override;
    std::string getFieldOfStudy(void) const override;
    void setFieldOfStudy(const std::string & fldOfStudy) override;

    std::string serialize(void) const override;

    void show(void) const override;
    void showExtented(void) const override;
    void modify(void) override;
};