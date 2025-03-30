#pragma once
#include "Entity.hpp"
#include "Student.hpp"

class UserInputHandler
{
public:
    static unsigned int getIndexFromUser(void);
    static std::string getNameFromUser(void);
    static std::string getLastnameFromUser(void);
    static std::tm getBirthdateFromUser(void);
    static std::string getAddressFromUser(void);
    static std::string getPeselFromUser(void);
    static Gender getGenderFromUser(void);
    static FieldOfStudy getFieldOfStudyFromUser(void);
    static subjects_t getSubjectsFromUser(void);
    static gradesToSubject_t getGradesFromUser(subjects_t subj);
    static AcademicTitle getAcademicTitleFromUser(void);
    static Department getDepartmentFromUser(void);

    static unsigned int modifyIndexByUser(const unsigned int & current_idx);
    static std::string modifyNameByUser(const std::string & current_name);
    static std::string modifyLastnameByUser(const std::string & current_lastname);
    static std::tm modifyBirthdateByUser(const std::tm & current_birthdate);
    static std::string modifyAddressByUser(const std::string & current_addr);
    static std::string modifyPeselByUser(const std::string & current_pesel);
    static Gender modifyGenderByUser(const Gender & current_gender);
    static FieldOfStudy modifyFieldOfStudyByUser(const FieldOfStudy & current_fieldofstudy);
    static subjects_t modifySubjectsByUser(const subjects_t & current_subjects);
    static gradesToSubject_t modifyGradesByUser(subjects_t subj, gradesToSubject_t current_grades);
    static AcademicTitle modifyAcademicTitleByUser(const AcademicTitle & current_title);
    static Department modifyDepartmentByUser(const Department & current_department);
};