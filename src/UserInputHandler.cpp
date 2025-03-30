#include "UserInputHandler.hpp"
#include "EntityUtils.hpp"
#include <algorithm>

extern std::map<std::string, FieldOfStudy> stringToFieldOfStudyMapping;
extern std::map<std::string, Subject> stringToSubjectMapping;
extern std::map<std::string, AcademicTitle> stringToAcademicTitleMapping;
extern std::map<std::string, Department> stringToDepartmentMapping;

unsigned int UserInputHandler::getIndexFromUser(void)
{
    std::string input;
    int indexNumber = 0;

    while (true) 
    {
        std::cout << getPrintHeader() << "Index number (max 6 digits):";
        std::getline(std::cin, input);

        try 
        {
            if (input.find_first_not_of("0123456789") != std::string::npos) 
            {
                throw std::invalid_argument("Entered invalid characters!");
            }

            indexNumber = std::stoi(input);

            if (input.length() > 6) 
            {
                throw std::out_of_range("Index lenght cannot be greater than 6 digits!");
            }

            break;

        } 
        catch (const std::exception& e) 
        {
            std::cerr << "[ERROR] " << e.what() << " Try again." << std::endl;
        }
    }

    return indexNumber;
}

std::string UserInputHandler::getNameFromUser(void)
{
    std::string input;

    while (true) 
    {
        std::cout << getPrintHeader() << "Name:";
        std::getline(std::cin, input);

        try 
        {
            if (input.find_first_of("0123456789") != std::string::npos) 
            {
                throw std::invalid_argument("Entered digit in name!");
            }

            if (input.find(' ') != std::string::npos) 
            {
                throw std::invalid_argument("Name must be a single word (no spaces)!");
            }

            break;

        } 
        catch (const std::exception& e) 
        {
            std::cerr << "[ERROR] " << e.what() << " Try again." << std::endl;
        }
    }

    return input;
}

std::string UserInputHandler::getLastnameFromUser(void)
{
    std::string input;

    while (true) 
    {
        std::cout << getPrintHeader() << "Lastname:";
        std::getline(std::cin, input);

        try 
        {
            if (input.find_first_of("0123456789") != std::string::npos) 
            {
                throw std::invalid_argument("Entered digit in name!");
            }

            if (input.find(' ') != std::string::npos) 
            {
                throw std::invalid_argument("Lastname must be a single word (no spaces)!");
            }

            break;

        } 
        catch (const std::exception& e) 
        {
            std::cerr << "[ERROR] " << e.what() << " Try again." << std::endl;
        }
    }

    return input;
}

std::tm UserInputHandler::getBirthdateFromUser() 
{
    std::string input;
    std::tm birthdate;

    while (true) 
    {
        try 
        {
            std::cout << getPrintHeader() << "Birthdate..." << std::endl << "\tDay: ";
            std::getline(std::cin, input);
            birthdate.tm_mday = std::stoi(input);

            if (birthdate.tm_mday < 1 || birthdate.tm_mday > 31) 
            {
                throw std::out_of_range("Day must be between 1-31.");
            }

            std::cout << "\tMonth: ";
            std::getline(std::cin, input);
            birthdate.tm_mon = std::stoi(input);
            
            if (birthdate.tm_mon < 1 || birthdate.tm_mon > 12) 
            {
                throw std::out_of_range("Month must be between 1-12.");
            }

            std::cout << "\tYear: ";
            std::getline(std::cin, input);
            birthdate.tm_year = std::stoi(input);
            
            if (birthdate.tm_year < 1900 || birthdate.tm_year > 2010) 
            {
                throw std::out_of_range("Year must be greater than or equal to 1900 and less than 2010.");
            }

            birthdate.tm_mon -= 1; // january = 0
            birthdate.tm_year -= 1900; // tm_year start from 1900

            break;

        } 
        catch (const std::exception& e) 
        {
            std::cerr << "[Error] " << e.what() << " Try again." << std::endl;
        }
    }

    return birthdate;
}

std::string UserInputHandler::getAddressFromUser(void)
{
    std::string input;

    while (true) 
    {
        std::cout << getPrintHeader() << "Residential address:";
        std::getline(std::cin, input);

        try 
        {
            // To do if something needed to validate
            // if (input.find_first_of("0123456789") != std::string::npos) 
            // {
            //     throw std::invalid_argument("Entered digit in name!");
            // }

            break;

        } 
        catch (const std::exception& e) 
        {
            std::cerr << "[ERROR] " << e.what() << " Try again." << std::endl;
        }
    }

    return input;
}

std::string UserInputHandler::getPeselFromUser(void)
{
    std::string input;

    while (true) 
    {
        std::cout << getPrintHeader() << "Pesel number (11 digits):";
        std::getline(std::cin, input);

        try 
        {
            if (input.find_first_not_of("0123456789") != std::string::npos) 
            {
                throw std::invalid_argument("Entered invalid characters!");
            }

            if (input.length() != 11) 
            {
                throw std::out_of_range("The PESEL number must contain 11 digits!");
            }

            break;

        } 
        catch (const std::exception& e) 
        {
            std::cerr << "[ERROR] " << e.what() << " Try again." << std::endl;
        }
    }

    return input;
}

Gender UserInputHandler::getGenderFromUser(void)
{
    std::string input;
    Gender gnr;

    while (true) 
    {
        std::cout << getPrintHeader() << "Gender (Male, Female, Default):";
        std::getline(std::cin, input);

        try 
        {
            gnr = stringToGender(input);
            break;
        } 
        catch (const std::exception& e) 
        {
            std::cerr << "[ERROR] " << e.what() << " Try again." << std::endl;
        }
        
    }

    return gnr;
}

FieldOfStudy UserInputHandler::getFieldOfStudyFromUser(void)
{
    std::string input;
    FieldOfStudy fieldOfStudy;

    while (true) 
    {
        std::cout << getPrintHeader() << "Field of Study (";
        for (const auto& entry : stringToFieldOfStudyMapping) {
            std::cout << entry.first << ',';
        }
        std::cout << "): " << std::endl;
        std::getline(std::cin, input);

        try 
        {
            fieldOfStudy = stringToFieldOfStudy(input);
            break;
        } 
        catch (const std::exception& e) 
        {
            std::cerr << "[ERROR] " << e.what() << " Try again." << std::endl;
        }
        
    }

    return fieldOfStudy;
}

subjects_t UserInputHandler::getSubjectsFromUser(void)
{
    std::string input;
    subjects_t subjects;

    while (true) 
    {
        std::cout << getPrintHeader() << "Subjects ( Available:";
        for (const auto& entry : stringToSubjectMapping) {
            std::cout << entry.first << ',';
        }
        std::cout << ")" << std::endl << "Format: 'Philosophy; Algebra; Psychology;' :" << std::endl;
        std::getline(std::cin, input);

        try 
        {
            if (input.empty())
            {
                throw std::invalid_argument("Entered empty string");
            }
            subjects = stringToSubjects(input);
            break;
        } 
        catch (const std::exception& e) 
        {
            std::cerr << "[ERROR] " << e.what() << " Try again." << std::endl;
        }
        
    }

    return subjects;
}

gradesToSubject_t UserInputHandler::getGradesFromUser(subjects_t subj)
{
    std::string input;
    gradesToSubject_t gradesToSubject;
    float grade;
    std::set<float> validGrades = {2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0};

    /* Iterate for entered subjects and add grades to list */
    for(auto & subject : subj)
    {
        grades_t grades;
        while(true)
        {
            std::cout << getPrintHeader() << "Enter grade for subject: " << subjectToString(subject) << std::endl;
            std::cout << "Expected value from set: {2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0}" << std::endl;
            std::cout << "Enter 'ESC' to stop adding grades for " << subjectToString(subject) << std::endl;

            std::getline(std::cin, input);

            if("ESC" == input) break;

            try 
            {
                grade = std::stof(input);
                if (validGrades.find(grade) == validGrades.end())
                {
                    throw std::out_of_range("Grade must be one of the given expected values.");
                }
                grades.push_back(std::stof(input));

            } 
            catch (const std::exception& e) 
            {
                std::cerr << "[ERROR] " << e.what() << " Try again." << std::endl;
            }

            std::cout << "Current grades for" << subjectToString(subject) << ": { ";
            for( auto grade : grades )
            {
                std::cout << grade << ", ";
            }
            std::cout << " }" << std::endl;
        }
        gradesToSubject.insert({subject, grades});
    }

    return gradesToSubject;
}

AcademicTitle UserInputHandler::getAcademicTitleFromUser(void)
{
    std::string input;
    AcademicTitle acdtitle;

    while (true) 
    {
        std::cout << getPrintHeader() << "Academic Title ( Available: ";
        for (const auto& entry : stringToAcademicTitleMapping) {
            std::cout << entry.first << ',';
        }
        std::cout << "):" << std::endl;
        std::getline(std::cin, input);

        try 
        {
            acdtitle = stringToAcademicTitle(input);
            break;

        } 
        catch (const std::exception& e) 
        {
            std::cerr << "[ERROR] " << e.what() << " Try again." << std::endl;
        }
    }

    return acdtitle;
}

Department UserInputHandler::getDepartmentFromUser(void)
{
    std::string input;
    Department department;

    while (true) 
    {
        std::cout << getPrintHeader() << "Department: ( Available:";
        for (const auto& entry : stringToDepartmentMapping) {
            std::cout << entry.first << ',';
        }
        std::cout << "):" << std::endl;
        std::getline(std::cin, input);

        try 
        {
            department = stringToDepartment(input);
            break;
        } 
        catch (const std::exception& e) 
        {
            std::cerr << "[ERROR] " << e.what() << " Try again." << std::endl;
        }
    }

    return department;
}


unsigned int UserInputHandler::modifyIndexByUser(const unsigned int & current_idx)
{
    std::string input;
    unsigned int index = 0;

    while (true) 
    {
        std::cout << getPrintHeader() << "Current Index number: " << current_idx << std::endl << "Enter new Index number or skip(Enter): ";
        std::getline(std::cin, input);

        try 
        {
            if (input.find_first_not_of("0123456789") != std::string::npos) 
            {
                throw std::invalid_argument("Entered invalid characters!");
            }

            if (input.length() > 6) 
            {
                throw std::out_of_range("Index lenght cannot be greater than 6 digits!");
            }

            index = input.empty() ? current_idx : std::stoi(input);
            break;

        } 
        catch (const std::exception& e) 
        {
            std::cerr << "[ERROR] " << e.what() << " Try again." << std::endl;
        }
    }

    return index;
}


std::string UserInputHandler::modifyNameByUser(const std::string & current_name)
{
    std::string input;
    std::string name;

    while (true) 
    {
        std::cout << getPrintHeader() << "Current Name: " << current_name << std::endl << "Enter new Name or skip(Enter): ";
        std::getline(std::cin, input);

        try 
        {
            if (input.find_first_of("0123456789") != std::string::npos) 
            {
                throw std::invalid_argument("Entered digit in name!");
            }

            if (input.find(' ') != std::string::npos) 
            {
                throw std::invalid_argument("Name must be a single word (no spaces)!");
            }

            name = input.empty() ? current_name : input;
            break;

        } 
        catch (const std::exception& e) 
        {
            std::cerr << "[ERROR] " << e.what() << " Try again." << std::endl;
        }
    }

    return name;
}


std::string UserInputHandler::modifyLastnameByUser(const std::string & current_lastname)
{
    std::string input;
    std::string lastname;

    while (true) 
    {
        std::cout << getPrintHeader() << "Current Lastname: " << current_lastname << std::endl << "Enter new Lastname or skip(Enter): ";
        std::getline(std::cin, input);

        try 
        {
            if (input.find_first_of("0123456789") != std::string::npos) 
            {
                throw std::invalid_argument("Entered digit in Lastname!");
            }

            if (input.find(' ') != std::string::npos) 
            {
                throw std::invalid_argument("Lastname must be a single word (no spaces)!");
            }

            lastname = input.empty() ? current_lastname : input;
            break;

        } 
        catch (const std::exception& e) 
        {
            std::cerr << "[ERROR] " << e.what() << " Try again." << std::endl;
        }
    }

    return lastname;
}

std::tm UserInputHandler::modifyBirthdateByUser(const std::tm & current_birthdate)
{
    std::string input;
    std::tm birthdate;

    while (true) 
    {
        try 
        {
            std::cout << getPrintHeader() << "Current birthday date: " << TmToString(current_birthdate, "%d.%m.%Y") << std::endl << "Enter new Birthday date or skip(Enter): " << std::endl;
            std::cout << "Birthdate..." << std::endl << "\tDay: ";
            std::getline(std::cin, input);

            /* If skip entering */
            if(input.empty())
            {
                birthdate = current_birthdate;
                break;
            }

            birthdate.tm_mday = std::stoi(input);

            if (birthdate.tm_mday < 1 || birthdate.tm_mday > 31) 
            {
                throw std::out_of_range("Day must be between 1-31.");
            }

            std::cout << "\tMonth: ";
            std::getline(std::cin, input);
            birthdate.tm_mon = std::stoi(input);
            
            if (birthdate.tm_mon < 1 || birthdate.tm_mon > 12) 
            {
                throw std::out_of_range("Month must be between 1-12.");
            }

            std::cout << "\tYear: ";
            std::getline(std::cin, input);
            birthdate.tm_year = std::stoi(input);
            
            if (birthdate.tm_year < 1900 || birthdate.tm_year > 2010) 
            {
                throw std::out_of_range("Year must be greater than or equal to 1900 and less than 2010.");
            }

            birthdate.tm_mon -= 1; // january = 0
            birthdate.tm_year -= 1900; // tm_year start from 1900

            break;

        } 
        catch (const std::exception& e) 
        {
            std::cerr << "[Error] " << e.what() << " Try again." << std::endl;
        }
    }

    return birthdate;
}

std::string UserInputHandler::modifyAddressByUser(const std::string & current_addr)
{
    std::string input;
    std::string address;

    while (true) 
    {
        std::cout << getPrintHeader() << "Current Pesel: " << current_addr << std::endl << "Enter new Pesel or skip(Enter): ";
        std::getline(std::cin, input);

        try 
        {
            // TBD
            // if (input.find_first_not_of("0123456789") != std::string::npos) 
            // {
            //     throw std::invalid_argument("Entered invalid characters!");
            // }

            address = input.empty() ? current_addr : input;
            break;

        } 
        catch (const std::exception& e) 
        {
            std::cerr << "[ERROR] " << e.what() << " Try again." << std::endl;
        }
    }

    return address;
}

std::string UserInputHandler::modifyPeselByUser(const std::string & current_pesel)
{
    std::string input;
    std::string pesel;

    while (true) 
    {
        std::cout << getPrintHeader() << "Current Pesel: " << current_pesel << std::endl << "Enter new Pesel or skip(Enter): ";
        std::getline(std::cin, input);

        try 
        {
            if (input.find_first_not_of("0123456789") != std::string::npos) 
            {
                throw std::invalid_argument("Entered invalid characters!");
            }

            if (input.length() > 0 && input.length() != 11) 
            {
                throw std::out_of_range("The PESEL number must contain 11 digits!");
            }

            pesel = input.empty() ? current_pesel : input;
            break;

        } 
        catch (const std::exception& e) 
        {
            std::cerr << "[ERROR] " << e.what() << " Try again." << std::endl;
        }
    }

    return pesel;
}

Gender UserInputHandler::modifyGenderByUser(const Gender & current_gender)
{
    std::string input;
    Gender gnr;

    while (true) 
    {
        std::cout << getPrintHeader() << "Current Gender: " << current_gender << std::endl;
        std::cout << "Available Genders: {Male, Female, Default}" << std::endl;
        std::cout << "Enter new Gender or skip(Enter): ";
        std::getline(std::cin, input);

        try 
        {
            gnr = input.empty() ? current_gender : stringToGender(input);
            break;
        } 
        catch (const std::exception& e) 
        {
            std::cerr << "[ERROR] " << e.what() << " Try again." << std::endl;
        }
        
    }

    return gnr;
}

FieldOfStudy UserInputHandler::modifyFieldOfStudyByUser(const FieldOfStudy & current_fieldofstudy)
{
    std::string input;
    FieldOfStudy fieldOfStudy;

    while (true) 
    {
        std::cout << getPrintHeader() << "Current Field of Study: " << fieldOfStudyToString(current_fieldofstudy) << std::endl;
        std::cout << "Available Field of Study: {";
        for (const auto& entry : stringToFieldOfStudyMapping) {
            std::cout << entry.first << ", ";
        }
        std::cout << "}" << std::endl << "Enter new Field of Study or skip(Enter): ";
        std::getline(std::cin, input);

        try 
        {
            fieldOfStudy = input.empty() ? current_fieldofstudy : stringToFieldOfStudy(input);
            break;
        } 
        catch (const std::exception& e) 
        {
            std::cerr << "[ERROR] " << e.what() << " Try again." << std::endl;
        }
        
    }

    return fieldOfStudy;
}

subjects_t UserInputHandler::modifySubjectsByUser(const subjects_t & current_subjects)
{
    std::string input;
    subjects_t subjects;

    while (true) 
    {
        std::cout << getPrintHeader() << "Current Subjects: [";
        for(const auto & sub : current_subjects)
        {
            std::cout << subjectToString(sub) << ", ";
        }
        std::cout << "]" << std::endl;
        std::cout  << "Available Subjects: {";
        for (const auto& entry : stringToSubjectMapping) {
            std::cout << entry.first << ", ";
        }
        std::cout << "}" << std::endl;
        std::cout << "Enter new Subjects(format: 'Math, Computer Science, Physics') or skip(Enter): ";
        std::getline(std::cin, input);

        try 
        {
            if (input.empty())
            {
                subjects = current_subjects;
            }

            std::stringstream ss(input);
            std::string token;

            while (std::getline(ss, token, ',')) 
            {
                std::erase_if(token, ::isspace);
                Subject subj = stringToSubject(token);
                subjects.insert(subj);
            }

            break;
        } 
        catch (const std::exception& e) 
        {
            std::cerr << "[ERROR] " << e.what() << " Try again." << std::endl;
        }
        
    }

    return subjects;
}

gradesToSubject_t UserInputHandler::modifyGradesByUser(subjects_t subj, gradesToSubject_t current_grades)
{
    std::string input;
    gradesToSubject_t gradesToSubject;
    float grade;
    std::set<float> validGrades = {2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0};

    /* Iterate for entered subjects and add grades to list */
    for(auto & subject : subj)
    {
        grades_t grades;
        while(true)
        {
            std::cout << getPrintHeader() << "Current grades for subject " << subjectToString(subject) << ": [";
            for(const auto & grade : current_grades[subject])
            {
                std::cout << grade << ", ";
            }
            std::cout << "]" << std::endl;
            std::cout << "Available Grades: {2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0}" << std::endl;
            std::cout << "Enter new Grades(format: '5.0, 2.5, 3.5) for " << subjectToString(subject) << " or skip(Enter): ";

            std::getline(std::cin, input);

            try 
            {
                if(input.empty())
                {
                    gradesToSubject.insert({subject, current_grades.at(subject)});
                    break;
                }

                
                std::stringstream ss(input);
                std::string token;

                while (std::getline(ss, token, ',')) 
                {
                    float grade = std::stof(token);
                    if (validGrades.find(grade) == validGrades.end()) 
                    {
                        throw std::invalid_argument("Grade must be one of the given expected values.");
                    }
                    grades.push_back(grade);   
                }
                break;
            }
            catch (const std::exception& e) 
            {
                std::cerr << "[ERROR] " << e.what() << " Try again." << std::endl;
            }
        }
        gradesToSubject.insert({subject, grades});
    }

    return gradesToSubject;
}

AcademicTitle UserInputHandler::modifyAcademicTitleByUser(const AcademicTitle & current_title)
{
    std::string input;
    AcademicTitle acdtitle;

    while (true) 
    {
        std::cout << getPrintHeader() << "Current Academic Title: " << academicTitleToString(current_title) << std::endl;
        std::cout << "Available Academic Title: {";
        for (const auto& entry : stringToAcademicTitleMapping) {
            std::cout << entry.first << ", ";
        }
        std::cout << "}:" << std::endl;
        std::cout << "Enter new Academic Title or skip(Enter): ";
        
        std::getline(std::cin, input);

        try 
        {
            if (input.empty())
            {
                acdtitle = current_title;
                break;
            }
            acdtitle = stringToAcademicTitle(input);
            break;

        } 
        catch (const std::exception& e) 
        {
            std::cerr << "[ERROR] " << e.what() << " Try again." << std::endl;
        }
    }

    return acdtitle;
}

Department UserInputHandler::modifyDepartmentByUser(const Department & current_department)
{
    std::string input;
    Department department;

    while (true) 
    {
        std::cout << getPrintHeader() << "Current Department: " << departmentToString(current_department) << std::endl;
        std::cout << "Available Department: {";
        for (const auto& entry : stringToDepartmentMapping) {
            std::cout << entry.first << ", ";
        }
        std::cout << "}:" << std::endl;
        std::cout << "Enter new Department or skip(Enter): ";

        std::getline(std::cin, input);

        try 
        {
            if (input.empty())
            {
                department = current_department;
                break;
            }

            department = stringToDepartment(input);
            break;
        } 
        catch (const std::exception& e) 
        {
            std::cerr << "[ERROR] " << e.what() << " Try again." << std::endl;
        }
    }

    return department;
}


