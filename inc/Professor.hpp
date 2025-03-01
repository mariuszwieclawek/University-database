#pragma once
#include <map>
#include <iostream>
#include "Entity.hpp"
#include "Enums.hpp"


class Professor : public Entity
{
private:
    AcademicTitle m_academicTitle;
    Department m_department;
public:
    Professor(int indexNumber, const std::string & name, const std::string & lastname, const std::tm & birthDate, const std::string & address = "default",
                const std::string & pesel = "default", const Gender & gender = Gender::Default, const AcademicTitle & acdtitle = AcademicTitle::DoctorHabilitatus,
                const Department & dprtm = Department::Mathematics);
                         
    Professor(int && indexNumber, std::string && name, std::string && lastname, std::tm && birthDate, std::string && address = "default",
                std::string && pesel = "default", Gender && gender = Gender::Default, AcademicTitle && acdtitle = AcademicTitle::DoctorHabilitatus,
                Department && dprtm = Department::Mathematics);
                    
    Professor(const Professor &other);

    Professor& operator==(const Professor & other);

    AcademicTitle getAcademicTitle(void) const;
    void setAcademicTitle(const AcademicTitle & title);
    Department getDepartment(void) const;
    void setDepartment(const Department & dep);

    EntityType getEntityType(void) const override;

    std::string serialize(void) const override;
    std::string infoToString(void) const override;
    std::string extendedInfoToString(void) const override;
};