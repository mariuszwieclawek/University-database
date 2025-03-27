#pragma once

#include "Student.hpp"  
#include "Professor.hpp"
#include "Entity.hpp"    
#include "EntityUtils.hpp"
#include <memory>
#include <string>
#include <ctime>

class EntityFactory 
{
public:
    static std::unique_ptr<Entity> createStudent(int indexNumber, const std::string& name, const std::string& lastname,
                                                 const std::tm& birthDate, const std::string& address, const std::string& pesel,
                                                 Gender gender, FieldOfStudy fieldofstudy, subjects_t subjects, gradesToSubject_t grades);

    static std::unique_ptr<Entity> createProfessor(int indexNumber, const std::string& name, const std::string& lastname,
                                                  const std::tm& birthDate, const std::string& address, const std::string& pesel,
                                                  Gender gender, AcademicTitle acdtitle, Department department);
};
