#include <iostream>
#include <sstream>

#include "UniversityDatabase.hpp"
#include "Student.hpp"

static std::vector<std::string> splitString(const std::string& str, char delimiter);


UniversityDatabase::UniversityDatabase(void)
{
    if( true == isCSVFileEmpty(m_file) )
    {
        std::string data = "Index, Entity Type, Name, Lastname, Date of birth, Address, PESEL, Gender, Field of study\n";
        appendToCSV(m_file, data);
    }
    else
    {
        readEntitiesFromCSV(m_file);
    }

}

UniversityDatabase::~UniversityDatabase(void)
{
    if (m_file.is_open()) 
    {
        m_file.close();
    }
}

bool UniversityDatabase::compareByLastnameAtoZ(const std::unique_ptr<Entity>& a, const std::unique_ptr<Entity>& b) 
{
    return a->getLastname() < b->getLastname();
}

bool UniversityDatabase::compareByLastnameZtoA(const std::unique_ptr<Entity>& a, const std::unique_ptr<Entity>& b) 
{
    return a->getLastname() > b->getLastname();
}

bool UniversityDatabase::compareByIndexAscending(const std::unique_ptr<Entity>& a, const std::unique_ptr<Entity>& b) 
{
    return a->getIndex() < b->getIndex();
}

bool UniversityDatabase::compareByIndexDescending(const std::unique_ptr<Entity>& a, const std::unique_ptr<Entity>& b) 
{
    return a->getIndex() > b->getIndex();
}

void UniversityDatabase::appendToCSV(std::fstream& file, const std::string& data) 
{
    file.open(m_entitiesFilename, std::ios::app);

    if (!file.is_open()) 
    {
        std::cerr << "\t[ERROR]\t" + std::string(__func__) + " function failed" << std::endl;
        exit(0);
    }
    
    file << data;

    file.close();
}

void UniversityDatabase::saveAllEntitiesToCSV(void) 
{
    m_file.open(m_entitiesFilename, std::ios::out | std::ios::trunc);

    if (!m_file.is_open()) 
    {
        std::cerr << "\t[ERROR]\t" + std::string(__func__) + " function failed" << std::endl;
        exit(0);
    }
    
    /* Write the header */
    m_file <<  "Index, Entity Type, Name, Lastname, Date of birth, Address, PESEL, Gender, Field of study\n";
    
    /* Write all entites */ 
    for (const auto& ent : m_entities) 
    {
        auto data = ent->serialize();
        m_file << data;
    }

    m_file.close();
}

bool UniversityDatabase::isCSVFileEmpty(std::fstream& file)
{
    bool isEmpty = false;

    file.open(m_entitiesFilename, std::ios::in | std::ios::app);
    if (!file.is_open()) 
    {
        std::cerr << "\t[ERROR]\t" + std::string(__func__) + " function failed" << std::endl;
        exit(0);
    }

    file.seekg(0, std::ios::end);
    isEmpty = file.tellg() == 0;
    file.close();

    return isEmpty;
}

void UniversityDatabase::readEntitiesFromCSV(std::fstream& file)
{
    file.open(m_entitiesFilename, std::ios::in);

    if (!file.is_open()) 
    {
        std::cerr << "\t[ERROR]\t" + std::string(__func__) + " function failed" << std::endl;
        exit(0);
    }

    std::string skipHeader;
    std::getline(file, skipHeader);

    std::string line;
    while(std::getline(file, line))
    {
        std::vector<std::string> objectFields = splitString(line, ',');

        if (objectFields.size() != 9) 
        {
            std::cerr << "\t[ERROR]\t" + std::string(__func__) + " function failed" << std::endl;
            exit(0);
        }

        Gender gender;
        std::tm birthdate;
        int index_number;
        try
        {
            index_number = std::stoi(objectFields[0]);
            birthdate = stringToTm(objectFields[4], "%d.%m.%Y");
            gender = stringToGender(objectFields[7]);
        }
        catch (const std::exception& e) 
        {
            std::cerr << "\t[ERROR]\t" << e.what() << std::endl;
            exit(0);
        }
  
        std::unique_ptr<Entity> student = std::make_unique<Student>(objectFields[2], objectFields[3], birthdate, objectFields[5], 
                                                                         index_number, objectFields[6], gender);
        m_entities.push_back(std::move(student));
    }

    file.close();
}

void UniversityDatabase::addEntity(std::unique_ptr<Entity> entity)
{
    std::string data = entity->serialize();

    appendToCSV(m_file, data); 

    m_entities.push_back(std::move(entity));
}

bool UniversityDatabase::removeEntityByPesel(const std::string & pesel)
{
    bool isRemoved = false;
    auto it = std::remove_if(m_entities.begin(), m_entities.end(),
                                [&pesel](const std::unique_ptr<Entity> & st){return st->getPesel() == pesel;} );

    isRemoved = (it != m_entities.end());
                                
    m_entities.erase(it, m_entities.end());

    /* Update entities in the file*/
    this->saveAllEntitiesToCSV();

    return isRemoved;
}

std::vector<const Entity*> UniversityDatabase::findEntitiesByLastname(const std::string & lastname)
{
    /* Return vector because there is a possibility to exist several entities with the same lastname */
    std::vector<const Entity*> foundEntities;
    for(const auto & s : m_entities)
    {
        if(s->getLastname() == lastname)
        {
            foundEntities.push_back(s.get());
        }
    }

    return foundEntities;
}

bool UniversityDatabase::modifyEntityByPesel(const std::string & pesel)
{
    auto it = std::find_if(m_entities.begin(), m_entities.end(),
                            [&pesel](const std::unique_ptr<Entity> & st){return st->getPesel() == pesel;});

    if (it == m_entities.end())
    {
        return false;
    }

    (*it)->modify();
    this->saveAllEntitiesToCSV();
    
    return true;
}

void UniversityDatabase::sortEntities(SortOrder order)
{
    switch(order)
    {
        case SORT_BY_LASTNAME_A_TO_Z:
        {
            std::sort(m_entities.begin(), m_entities.end(), UniversityDatabase::compareByLastnameAtoZ);
            break;
        }
        case SORT_BY_LASTNAME_Z_TO_A:
        {
            std::sort(m_entities.begin(), m_entities.end(), UniversityDatabase::compareByLastnameZtoA);
            break;
        }
        case SORT_BY_INDEX_ASCENDING:
        {
            std::sort(m_entities.begin(), m_entities.end(), UniversityDatabase::compareByIndexAscending);
            break;
        }
        case SORT_BY_INDEX_DESCENDING:
        {
            std::sort(m_entities.begin(), m_entities.end(), UniversityDatabase::compareByIndexDescending);
            break;
        }
        default:
        {
            std::sort(m_entities.begin(), m_entities.end(), UniversityDatabase::compareByLastnameAtoZ);
            break;
        }
            
    }
    
    this->saveAllEntitiesToCSV();
}

void UniversityDatabase::displayEntities(void) const
{
    if (m_entities.empty()) {
        std::cout << "University database is empty." << std::endl;
        return;
    }

    std::cout << "===========================================================================================================" << std::endl;
    std::cout << "| Index | Entity type | Name | Last name | Birthday | Address | PESEL | Gender | Field of study |" << std::endl;
    std::cout << "===========================================================================================================" << std::endl;
    for(const auto & ent : m_entities)
    {
        ent->show();
    }
}

void UniversityDatabase::displayEntitiesByFieldOfStudy(const std::string & fldOfStd) const
{
    std::vector<Entity*> entForSelecedFldOfStd;

    for(const auto & ent : m_entities)
    {
        if(ent->getFieldOfStudy() == fldOfStd)
        {
            entForSelecedFldOfStd.push_back(ent.get());
        }
    }

    if(entForSelecedFldOfStd.empty()) return;

    std::cout << "===========================================================================================================" << std::endl;
    std::cout << "| Index | Entity type | Name | Last name | Birthday | Address | PESEL | Gender | Field of study |" << std::endl;
    std::cout << "===========================================================================================================" << std::endl;
    for(const auto & ent : m_entities)
    {
        ent->show();
    }
}

std::set<std::string> UniversityDatabase::getFieldsOfStudy(void) const
{
    std::set<std::string> fields_of_study;

    if (m_entities.empty()) {
        std::cout << "Entity database is empty." << std::endl;
        return fields_of_study;
    }

    for(const auto & ent : m_entities)
    {
        fields_of_study.insert(ent->getFieldOfStudy());
    }
    
    return fields_of_study;
}

std::set<std::string> UniversityDatabase::getSubjectsForSelectedFieldOfStudy(const std::string & fldOfStd) const
{
    std::vector<Entity*> entForSelecedFldOfStd;
    std::set<std::string> subjects;

    for(const auto & ent : m_entities)
    {
        if(ent->getFieldOfStudy() == fldOfStd)
        {
            entForSelecedFldOfStd.push_back(ent.get());
        }
    }

    if(entForSelecedFldOfStd.empty()) return subjects;

    /* Every entities have the same mandatory subjects so we can use get subjects for any entity */
    return entForSelecedFldOfStd[0]->getMandatorySubjects();
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

