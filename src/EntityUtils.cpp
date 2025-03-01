#include "EntityUtils.hpp"
#include "Professor.hpp"
#include <algorithm>

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


std::string setToString(const std::set<std::string>& st) 
{
    std::stringstream ss;
    for (auto it = st.begin(); it != st.end(); ++it) 
    {
        ss << *it;
        if (std::next(it) != st.end())
        {  
            ss << "; ";  
        }
    }
    return ss.str();
}

std::set<std::string> stringToSet(const std::string& str) 
{
    std::set<std::string> result;
    std::stringstream ss(str);
    std::string temp;
    
    while (std::getline(ss, temp, ';')) 
    {
        temp.erase(0, temp.find_first_not_of(' ')); // remove space in front
        temp.erase(temp.find_last_not_of(' ') + 1); // remove space from the back
        
        if (!temp.empty()) result.insert(temp);
    }
    
    return result;
}

std::map<std::string, std::vector<float>> parseGrades(const std::string& data) 
{
    std::map<std::string, std::vector<float>> m_grades;

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

            m_grades[subject] = grades;
        }
    }

    return m_grades;
}


std::string gradesToString(const std::map<std::string, std::vector<float>>& m_grades) 
{
    std::ostringstream oss; 
    for (const auto& [subject, grades] : m_grades)
    {
        oss << subject << "={" ;
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



AcademicTitle stringToAcademicTitle(const std::string& str) 
{
    auto it = stringToAcademicTitleMapping.find(str);
    if (it != stringToAcademicTitleMapping.end())
    {
        return it->second;
    }
    else
    {
        throw std::runtime_error(std::string(__func__) + " function failed");
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
        throw std::runtime_error(std::string(__func__) + " function failed");
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