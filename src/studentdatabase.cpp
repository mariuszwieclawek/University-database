#include <iostream>
#include <sstream>

#include "studentdatabase.hpp"
#include "mathStudent.hpp"

static std::vector<std::string> splitString(const std::string& str, char delimiter);
static Gender stringToGender(const std::string& str);


StudentDatabase::StudentDatabase(void)
{
    if( true == isCSVFileEmpty(m_file) )
    {
        std::vector<std::string> data = 
        {
            "Name", "Lastname", "Address", "Index number", "PESEL", "Gender",
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
        std::cout << value << std::endl;
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
        std::cerr << "\t[ERROR]\t{appendToCSV} - file is closed " << std::endl;
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

        if (objectFields.size() != 6) 
        {
            std::cerr << "\t[ERROR]\t{readStudentsFromCSV} - invalid input data " << std::endl;
            exit(0);
        }

        Gender gender = stringToGender(objectFields[5]);
  
        std::unique_ptr<Student> student = std::make_unique<MathStudent>(objectFields[0], objectFields[1], objectFields[2], 
                                                                        std::stoi(objectFields[3]), objectFields[4], gender);
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

    return isRemoved;
}

std::vector<Student*> StudentDatabase::findStudentByLastname(const std::string & lastname)
{
    std::vector<Student*> foundStudents;
    for(const auto & s : m_students)
    {
        if(s->getLastname() == lastname)
        {
            foundStudents.push_back(s.get());
        }
    }

    return foundStudents;
}

void StudentDatabase::sortStudentByLastname(void)
{
    std::sort(m_students.begin(), m_students.end(), 
    [](const std::unique_ptr<Student> & st1, const std::unique_ptr<Student> & st2){return st1->getLastname() < st2->getLastname();});
}

void StudentDatabase::displayStudents(void) const
{
    if (m_students.empty()) {
        std::cout << "Baza danych jest pusta." << std::endl;
        return;
    }

    std::cout << "===========================================================================================\n";
    std::cout << "| No. | Name | Last name | Address | Index number | PESEL | Sex |\n";
    std::cout << "===========================================================================================\n";
    int no=1;
    for(const auto & st : m_students)
    {
        std::cout << "| " << no << " | ";
        st->showStudent();
        no++;
    }
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


static Gender stringToGender(const std::string& str) 
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
        std::cerr << "\t[ERROR]\t{stringToGender} - invalid input data " << std::endl;
        exit(0);
    }
}