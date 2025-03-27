#include "EntityFactory.hpp"
#include "Student.hpp"
#include "Professor.hpp"
#include "Entity.hpp"

std::unique_ptr<Entity> EntityFactory::createStudent(int indexNumber, const std::string& name, const std::string& lastname,
                                                     const std::tm& birthDate, const std::string& address, const std::string& pesel,
                                                     Gender gender, FieldOfStudy fieldofstudy, subjects_t subjects, gradesToSubject_t grades) 
{
    return std::make_unique<Student>(indexNumber, name, lastname, birthDate, address, pesel, gender, fieldofstudy, subjects, grades);
}

std::unique_ptr<Entity> EntityFactory::createProfessor(int indexNumber, const std::string& name, const std::string& lastname,
                                                      const std::tm& birthDate, const std::string& address, const std::string& pesel,
                                                      Gender gender, AcademicTitle acdtitle, Department department) 
{
    return std::make_unique<Professor>(indexNumber, name, lastname, birthDate, address, pesel, gender, acdtitle, department);
}
