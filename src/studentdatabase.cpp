#include <iostream>
#include <sstream>

#include "studentdatabase.hpp"
#include "mathStudent.hpp"

static std::vector<std::string> splitString(const std::string& str, char delimiter);


StudentDatabase::StudentDatabase(void)
{
    if( true == isCSVFileEmpty(m_file) )
    {
        std::vector<std::string> data = 
        {
            "Name", "Lastname", "Birthdate", "Address", "Index number", "PESEL", "Gender",
        };

        appendToCSV(m_file, data);
    }
    else
    {
        readStudentsFromCSV(m_file);
    }

}

StudentDatabase::~StudentDatabase(void)
{
    if (m_file.is_open()) 
    {
        m_file.close();
    }
}

bool StudentDatabase::compareByLastnameAtoZ(const std::unique_ptr<Student>& a, const std::unique_ptr<Student>& b) 
{
    return a->getLastname() < b->getLastname();
}

bool StudentDatabase::compareByLastnameZtoA(const std::unique_ptr<Student>& a, const std::unique_ptr<Student>& b) 
{
    return a->getLastname() > b->getLastname();
}

bool StudentDatabase::compareByIndexAscending(const std::unique_ptr<Student>& a, const std::unique_ptr<Student>& b) 
{
    return a->getIndex() < b->getIndex();
}

bool StudentDatabase::compareByIndexDescending(const std::unique_ptr<Student>& a, const std::unique_ptr<Student>& b) 
{
    return a->getIndex() > b->getIndex();
}

void StudentDatabase::appendToCSV(std::fstream& file, const std::vector<std::string>& data) 
{
    file.open(m_studentsFilename, std::ios::app);

    if (!file.is_open()) 
    {
        std::cerr << "\t[ERROR]\t{appendToCSV} - file is closed " << std::endl;
        exit(0);
    }
    
    for (const auto& value : data) 
    {
        file << value << ",";
    }
    file << "\n";

    file.close();
}

void StudentDatabase::saveAllStudentsToCSV(void) 
{
    m_file.open(m_studentsFilename, std::ios::out | std::ios::trunc);

    if (!m_file.is_open()) 
    {
        std::cerr << "\t[ERROR]\t{saveAllStudentsToCSV} - file is closed " << std::endl;
        exit(0);
    }
    
    /* Write the header */
    m_file << "Name,Lastname,Address,Index number,PESEL,Gender\n";

    /* Write all students */ 
    for (const auto& student : m_students) 
    {
        auto data = student->getStudent();
        for (const auto& value : data) 
        {
            m_file << value << ",";
        }
        m_file << "\n";
    }

    m_file.close();
}

bool StudentDatabase::isCSVFileEmpty(std::fstream& file)
{
    bool isEmpty = false;

    file.open(m_studentsFilename, std::ios::in | std::ios::app);
    if (!file.is_open()) 
    {
        std::cerr << "\t[ERROR]\t{isCSVFileEmpty} - file is closed " << std::endl;
        exit(0);
    }

    file.seekg(0, std::ios::end);
    isEmpty = file.tellg() == 0;
    file.close();

    return isEmpty;
}

void StudentDatabase::readStudentsFromCSV(std::fstream& file)
{
    file.open(m_studentsFilename, std::ios::in);

    if (!file.is_open()) 
    {
        std::cerr << "\t[ERROR]\t{readStudentsFromCSV} - file is closed " << std::endl;
        exit(0);
    }

    std::string skipHeader;
    std::getline(file, skipHeader);

    std::string line;
    while(std::getline(file, line))
    {
        std::cout << line << std::endl;
        std::vector<std::string> objectFields = splitString(line, ',');

        if (objectFields.size() != 7) 
        {
            std::cerr << "\t[ERROR]\t{readStudentsFromCSV} - invalid input data " << std::endl;
            exit(0);
        }

        Gender gender;
        std::tm birthdate;
        try
        {
            gender = stringToGender(objectFields[6]);
            birthdate = stringToTm(objectFields[2], "%d.%m.%Y");
        }
        catch (const std::exception& e) 
        {
            std::cerr << "\t[ERROR]\t{readStudentsFromCSV} - " << e.what() << std::endl;
            exit(0);
        }
        
  
        std::unique_ptr<Student> student = std::make_unique<MathStudent>(objectFields[0], objectFields[1], birthdate, objectFields[3], 
                                                                         std::stoi(objectFields[4]), objectFields[5], gender);
        m_students.push_back(std::move(student));
    }

    file.close();
}

void StudentDatabase::addStudent(std::unique_ptr<Student> student)
{
    auto data = student->getStudent();

    appendToCSV(m_file, data); 

    m_students.push_back(std::move(student));
}

bool StudentDatabase::removeStudentByPesel(const std::string & pesel)
{
    bool isRemoved = false;
    auto it = std::remove_if(m_students.begin(), m_students.end(),
                                [&pesel](const std::unique_ptr<Student> & st){return st->getPesel() == pesel;} );

    isRemoved = (it != m_students.end());
                                
    m_students.erase(it, m_students.end());

    /* Update students in the file*/
    this->saveAllStudentsToCSV();

    return isRemoved;
}

std::vector<const Student*> StudentDatabase::findStudentsByLastname(const std::string & lastname)
{
    /* Return vector because there is a possibility to exist several students with the same lastname */
    std::vector<const Student*> foundStudents;
    for(const auto & s : m_students)
    {
        if(s->getLastname() == lastname)
        {
            foundStudents.push_back(s.get());
        }
    }

    return foundStudents;
}

bool StudentDatabase::modifyStudentByPesel(const std::string & pesel)
{
    auto it = std::find_if(m_students.begin(), m_students.end(),
                            [&pesel](const std::unique_ptr<Student> & st){return st->getPesel() == pesel;});

    if (it == m_students.end())
    {
        return false;
    }

    (*it)->modifyStudent();
    this->saveAllStudentsToCSV();
    
    return true;
}

void StudentDatabase::sortStudents(SortOrder order)
{
    switch(order)
    {
        case SORT_BY_LASTNAME_A_TO_Z:
        {
            std::sort(m_students.begin(), m_students.end(), StudentDatabase::compareByLastnameAtoZ);
            break;
        }
        case SORT_BY_LASTNAME_Z_TO_A:
        {
            std::sort(m_students.begin(), m_students.end(), StudentDatabase::compareByLastnameZtoA);
            break;
        }
        case SORT_BY_INDEX_ASCENDING:
        {
            std::sort(m_students.begin(), m_students.end(), StudentDatabase::compareByIndexAscending);
            break;
        }
        case SORT_BY_INDEX_DESCENDING:
        {
            std::sort(m_students.begin(), m_students.end(), StudentDatabase::compareByIndexDescending);
            break;
        }
        default:
        {
            std::sort(m_students.begin(), m_students.end(), StudentDatabase::compareByLastnameAtoZ);
            break;
        }
            
    }
    
    this->saveAllStudentsToCSV();
}

void StudentDatabase::displayStudents(void) const
{
    if (m_students.empty()) {
        std::cout << "Student database is empty." << std::endl;
        return;
    }

    std::cout << "===========================================================================================" << std::endl;
    std::cout << "| No. | Name | Last name | Birthday | Address | Index number | PESEL | Gender |" << std::endl;
    std::cout << "===========================================================================================" << std::endl;
    int no=1;
    for(const auto & st : m_students)
    {
        std::cout << "| " << no << " | ";
        st->showStudent();
        no++;
    }
}

void StudentDatabase::displayStudentsByFieldOfStudy(const std::string & fldOfStd) const
{
    std::vector<Student*> stdForSelecedFldOfStd;

    for(const auto & st : m_students)
    {
        if(st->getFieldOfStudy() == fldOfStd)
        {
            stdForSelecedFldOfStd.push_back(st.get());
        }
    }

    if(stdForSelecedFldOfStd.empty()) return;

    std::cout << "===========================================================================================" << std::endl;
    std::cout << "| No. | Name | Last name | Address | Index number | PESEL | Gender |" << std::endl;
    std::cout << "===========================================================================================" << std::endl;
    int no=1;
    for(const auto & std : stdForSelecedFldOfStd)
    {
        std::cout << "| " << no << " | ";
        std->showStudent();
        no++;
    }
}

std::set<std::string> StudentDatabase::getFieldsOfStudy(void) const
{
    std::set<std::string> fields_of_study;

    if (m_students.empty()) {
        std::cout << "Student database is empty." << std::endl;
        return fields_of_study;
    }

    for(const auto & st : m_students)
    {
        fields_of_study.insert(st->getFieldOfStudy());
    }
    
    return fields_of_study;
}

std::set<std::string> StudentDatabase::getSubjectsForSelectedFieldOfStudy(const std::string & fldOfStd) const
{
    std::vector<Student*> stdForSelecedFldOfStd;
    std::set<std::string> subjects;

    for(const auto & st : m_students)
    {
        if(st->getFieldOfStudy() == fldOfStd)
        {
            stdForSelecedFldOfStd.push_back(st.get());
        }
    }

    if(stdForSelecedFldOfStd.empty()) return subjects;

    /* Every students have the same mandatory subjects so we can use get subjects for any student */
    return stdForSelecedFldOfStd[0]->getMandatorySubjects();
}

static std::vector<std::string> splitString(const std::string& str, char delimiter) 
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    while (std::getline(tokenStream, token, delimiter)) 
    {
        tokens.push_back(token);
    }
    return tokens;
}

