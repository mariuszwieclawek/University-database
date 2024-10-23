#pragma once
#include <ctime>
#include <sstream>
#include <stdexcept>
#include <iomanip>
#include <set>
#include <map>
#include <vector>
#include "Entity.hpp"
#include "Professor.hpp"

Gender stringToGender(const std::string& str);
EntityType stringToEntityType(const std::string& str);
std::tm stringToTm(const std::string& dateStr, const std::string& format);
std::string TmToString(const std::tm & tmdate, const std::string& format);

std::ostream& operator<<(std::ostream & os, const Gender & gender);
std::istream& operator>>(std::istream & is, Gender & gender);
std::ostream& operator<<(std::ostream & os, const EntityType & entitytype);
std::istream& operator>>(std::istream & is, EntityType & entitytype);

std::string setToString(const std::set<std::string>& st);
std::set<std::string> stringToSet(const std::string& str);
std::map<std::string, std::vector<float>> parseGrades(const std::string& data);
std::string gradesToString(const std::map<std::string, std::vector<float>>& m_grades);

AcademicTitle stringToAcademicTitle(const std::string& str);
std::string academicTitleToString(AcademicTitle title);
Department stringToDepartment(const std::string& str);
std::string departmentToString(Department dep);