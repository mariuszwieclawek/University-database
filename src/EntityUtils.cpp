#include "EntityUtils.hpp"
#include "Professor.hpp"
#include <algorithm>

std::string getPrintHeader(void)
{
    return std::string("===================================================================================================================================================\n");
}

Gender stringToGender(const std::string& str) 
{
    if (str == "Male") 
    {
        return Gender::Male;
    } 
    else if (str == "Female") 
    {
        return Gender::Female;
    } 
    else if (str == "Default") 
    {
        return Gender::Default;
    } 
    else 
    {
        throw std::runtime_error(std::string(__func__) + " function failed");
    }
}

EntityType stringToEntityType(const std::string& str) 
{
    if (str == "Student") 
    {
        return EntityType::Student;
    } 
    else if (str == "Professor") 
    {
        return EntityType::Professor;
    } 
    else if (str == "Admin") 
    {
        return EntityType::Admin;
    }
    else if (str == "Staff") 
    {
        return EntityType::Staff;
    } 
    else 
    {
        throw std::runtime_error(std::string(__func__) + " function failed");
    }
}

std::tm stringToTm(const std::string& dateStr, const std::string& format) 
{
    std::tm tm = {};
    std::istringstream ss(dateStr);
    ss >> std::get_time(&tm, format.c_str());
    
    if (ss.fail())
    {
        throw std::runtime_error(std::string(__func__) + " function failed");
    }
    
    return tm;
}

std::string TmToString(const std::tm & tmdate, const std::string& format) 
{
    std::stringstream ssBirthday;
    ssBirthday << std::put_time(&tmdate, format.c_str());
    std::string birthdate = ssBirthday.str();
    
    return birthdate;
}

std::ostream& operator<<(std::ostream & os, const Gender & gender)
{
    switch (gender)
    {
    case Gender::Male:
        os << "Male";
        break;
    case Gender::Female:
        os << "Female";
        break;
    default:
        os << "Default";
        break;
    }
    return os;
}

std::istream& operator>>(std::istream& is, Gender& gender)
{
    std::string input;
    is >> input;

    if (input == "Male") 
    {
        gender = Gender::Male;
    } 
    else if (input == "Female") 
    {
        gender = Gender::Female;
    } 
    else 
    {
        gender = Gender::Default;
    }

    return is;
}

std::ostream& operator<<(std::ostream & os, const EntityType & entity_type)
{
    switch (entity_type)
    {
    case EntityType::Student:
        os << "Student";
        break;
    case EntityType::Professor:
        os << "Professor";
        break;
    case EntityType::Admin:
        os << "Admin";
        break;
    case EntityType::Staff:
        os << "Staff";
        break;
    }
    return os;
}

std::istream& operator>>(std::istream& is, EntityType & entity_type)
{
    std::string input;
    is >> input;

    if (input == "Student") 
    {
        entity_type = EntityType::Student;
    } 
    else if (input == "Professor") 
    {
        entity_type = EntityType::Professor;
    }
    else if (input == "Admin") 
    {
        entity_type = EntityType::Admin;
    }
    else if (input == "Staff") 
    {
        entity_type = EntityType::Staff;
    }

    return is;
}


std::string subjectsToString(const subjects_t & st)
{
    std::stringstream ss;
    for (auto it = st.begin(); it != st.end(); ++it) 
    {
        ss << subjectToString(*it);
        if (std::next(it) != st.end())
        {  
            ss << "; ";  
        }
    }
    return ss.str();
}

subjects_t stringToSubjects(const std::string& str)
{
    subjects_t result;
    std::stringstream ss(str);
    std::string temp;
    
    while (std::getline(ss, temp, ';')) 
    {
        temp.erase(0, temp.find_first_not_of(' ')); // remove space in front
        temp.erase(temp.find_last_not_of(' ') + 1); // remove space from the back
        
        if (!temp.empty())
        {
            result.insert(stringToSubject(temp));
        }
    }
    
    return result;
}

gradesToSubject_t parseGrades(const std::string& data)
{
    gradesToSubject_t m_grades;

    /* remove whitespace at the beginning and end */
    std::string trimmedData = data;
    trimmedData.erase(trimmedData.find_last_not_of(" ") + 1);
    trimmedData.erase(0, trimmedData.find_first_not_of(" "));

    std::stringstream ss(trimmedData);
    std::string item;

    while (std::getline(ss, item, ';')) 
    { 
        std::size_t pos = item.find('=');
        if (pos != std::string::npos) 
        {
            std::string subject = item.substr(0, pos); // key
            std::string gradesString = item.substr(pos + 1); // values

            gradesString.erase(std::remove(gradesString.begin(), gradesString.end(), '{'), gradesString.end());
            gradesString.erase(std::remove(gradesString.begin(), gradesString.end(), '}'), gradesString.end());

            /* separate grades based on a space */
            std::stringstream gradesStream(gradesString);
            std::string grade;
            std::vector<float> grades;

            while (std::getline(gradesStream, grade, ' ')) 
            {
                if (!grade.empty()) 
                {
                    grades.push_back(std::stof(grade));
                }
            }

            try 
            {
                m_grades[stringToSubject(subject)] = grades;
            } 
            catch (const std::exception& e) 
            {
                std::cerr << "[ERROR] " << e.what() << " The subject in the database does not match the list of available subjects." << std::endl;
                exit(0);
            }
                
        }
    }

    return m_grades;
}


std::string gradesToString(const gradesToSubject_t& m_grades) 
{
    std::ostringstream oss; 
    for (const auto& [subject, grades] : m_grades)
    {
        oss << subjectToString(subject) << "={" ;
        for (size_t i = 0; i < grades.size(); ++i)
        {
            oss << grades[i];
            if (i < grades.size() - 1)
            {
                oss << " ";
            }
        }
        oss << "};";
    }
    return oss.str();
}




std::map<std::string, AcademicTitle> stringToAcademicTitleMapping = 
{
    {"Associate Professor",     AcademicTitle::AssociateProfessor            },
    {"Professor"          ,     AcademicTitle::Professor                     },
    {"Titular Professor"  ,     AcademicTitle::TitularProfessor              },
    {"Doctor habilitatus" ,     AcademicTitle::DoctorHabilitatus             }
};

std::map<std::string, Department> stringToDepartmentMapping = 
{
    {"Computer Science"                  ,      Department::ComputerScience                           },
    {"Electronics and Telecommunications",      Department::ElectronicsAndTelecommunications          },
    {"Architecture"                      ,      Department::Architecture                              },
    {"Mathematics"                       ,      Department::Mathematics                               },
    {"Physics"                           ,      Department::Physics                                   },
    {"Chemistry"                         ,      Department::Chemistry                                 },
    {"Medicine"                          ,      Department::Medicine                                  },
    {"Pharmacy"                          ,      Department::Pharmacy                                  },
    {"Psychology"                        ,      Department::Psychology                                }
};

std::map<std::string, FieldOfStudy> stringToFieldOfStudyMapping =
{
    {"Computer Science"         , FieldOfStudy::ComputerScience         },
    {"Architecture"             , FieldOfStudy::Architecture            },
    {"Medicine"                 , FieldOfStudy::Medicine                },
    {"Law"                      , FieldOfStudy::Law                     },
    {"Business"                 , FieldOfStudy::Business                },
    {"Psychology"               , FieldOfStudy::Psychology              },
    {"Philosophy"               , FieldOfStudy::Philosophy              },
    {"Mathematics"              , FieldOfStudy::Mathematics             },
    {"Physics"                  , FieldOfStudy::Physics                 },
    {"Default"                  , FieldOfStudy::Default                 },
};

std::map<std::string, Subject> stringToSubjectMapping =
{
    {"Analytics"               , Subject::Analytics                 },
    {"Algebra"                  , Subject::Algebra                  },
    {"Data Structures"          , Subject::DataStructures           },
    {"Math"                     , Subject::Math                     },
    {"Economics"                , Subject::Economics                },
    {"Astrophysics"             , Subject::Astrophysics             },
    {"Physics"                  , Subject::Physics                  },
    {"Philosophy"               , Subject::Philosophy               },
    {"Psychology"               , Subject::Psychology               },
    {"Software Engineering"     , Subject::SoftwareEngineering      },
    {"Default"                  , Subject::Default                  }
};



AcademicTitle stringToAcademicTitle(const std::string& str) 
{
    auto it = stringToAcademicTitleMapping.find(str);
    if (it != stringToAcademicTitleMapping.end())
    {
        return it->second;
    }
    else
    {
        throw std::runtime_error(std::string(__func__) + " failed: Invalid academic title string '" + str + "'");
    }
}

std::string academicTitleToString(AcademicTitle title) 
{
    std::string titlestr;
    for (const auto& pair : stringToAcademicTitleMapping) 
    {
        if (pair.second == title) 
        {
            titlestr = pair.first;
            break;
        }
    }
    return titlestr;
}

Department stringToDepartment(const std::string& str) 
{
    auto it = stringToDepartmentMapping.find(str);
    if (it != stringToDepartmentMapping.end())
    {
        return it->second;
    }
    else
    {
        throw std::runtime_error(std::string(__func__) + " failed: Invalid department string '" + str + "'");
    }
}

std::string departmentToString(Department dep) 
{
    std::string depstr;
    for (const auto& pair : stringToDepartmentMapping) 
    {
        if (pair.second == dep) 
        {
            depstr = pair.first;
            break;
        }
    }
    return depstr;
}

FieldOfStudy stringToFieldOfStudy(const std::string& str) 
{
    auto it = stringToFieldOfStudyMapping.find(str);
    if (it != stringToFieldOfStudyMapping.end())
    {
        return it->second;
    }
    else
    {
        throw std::runtime_error(std::string(__func__) + " failed: Invalid field of study string '" + str + "'");
    }
}

std::string fieldOfStudyToString(FieldOfStudy field) 
{
    std::string fieldOfStudy;
    for (const auto& pair : stringToFieldOfStudyMapping) 
    {
        if (pair.second == field) 
        {
            fieldOfStudy = pair.first;
            break;
        }
    }
    return fieldOfStudy;
}

Subject stringToSubject(const std::string& subject) 
{
    auto it = stringToSubjectMapping.find(subject);
    if (it != stringToSubjectMapping.end())
    {
        return it->second;
    }
    else
    {
        throw std::runtime_error(std::string(__func__) + " failed: Invalid subject string '" + subject + "'");
    }
}

std::string subjectToString(Subject subj) 
{
    std::string subject;
    for (const auto& pair : stringToSubjectMapping) 
    {
        if (pair.second == subj) 
        {
            subject = pair.first;
            break;
        }
    }
    return subject;
}

