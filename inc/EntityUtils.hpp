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
#include "Student.hpp"

std::string getPrintHeader(void);

Gender stringToGender(const std::string& str);
EntityType stringToEntityType(const std::string& str);
std::tm stringToTm(const std::string& dateStr, const std::string& format);
std::string TmToString(const std::tm & tmdate, const std::string& format);

std::ostream& operator<<(std::ostream & os, const Gender & gender);
std::istream& operator>>(std::istream & is, Gender & gender);
std::ostream& operator<<(std::ostream & os, const EntityType & entitytype);
std::istream& operator>>(std::istream & is, EntityType & entitytype);

std::string subjectsToString(const subjects_t & st);
subjects_t stringToSubjects(const std::string& str);
gradesToSubject_t parseGrades(const std::string& data);
std::string gradesToString(const gradesToSubject_t& m_grades);

AcademicTitle stringToAcademicTitle(const std::string& str);
std::string academicTitleToString(AcademicTitle title);
Department stringToDepartment(const std::string& str);
std::string departmentToString(Department dep);
FieldOfStudy stringToFieldOfStudy(const std::string& str);
std::string fieldOfStudyToString(FieldOfStudy field);
Subject stringToSubject(const std::string& subject);
std::string subjectToString(Subject subj);
    

unsigned int getIndexFromUser(void);
std::tm getBirthdateFromUser(void);
std::string getPeselFromUser(void);
Gender getGenderFromUser(void);
FieldOfStudy getFieldOfStudyFromUser(void);
subjects_t getSubjectsFromUser(void);
gradesToSubject_t getGradesFromUser(subjects_t subj);