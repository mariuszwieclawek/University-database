#include "UniversityDatabase.hpp"
#include "EntityUtils.hpp"
#include "Student.hpp"
#include "Professor.hpp"
#include <iostream>
#include <sstream>
#include <memory>
#include <algorithm>

static std::vector<std::string> splitString(const std::string& str, char delimiter);


UniversityDatabase::UniversityDatabase(void)
{
    if( true == isCSVFileEmpty(m_file) )
    {
        std::string data = "Index, Entity Type, Name, Lastname, Date of birth, Address, PESEL, Gender, Field of study, Subjects, Grades, Academic Title, Department\n";
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
    m_file <<  "Index, Entity Type, Name, Lastname, Date of birth, Address, PESEL, Gender, Field of study, Subjects, Grades, Academic Title, Department\n";
    
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

        if (objectFields.size() != 13) 
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

        EntityType enttype = stringToEntityType(objectFields[1]);
        if(enttype == EntityType::Student)
        {
            std::unique_ptr<Entity> student = std::make_unique<Student>(index_number, objectFields[2], objectFields[3], birthdate, 
                                                            objectFields[5], objectFields[6], gender, objectFields[8], objectFields[9], objectFields[10]);
            m_entities.push_back(std::move(student));
        }
        else if(enttype == EntityType::Professor)
        {
            std::unique_ptr<Entity> proff = std::make_unique<Professor>(index_number, objectFields[2], objectFields[3], birthdate, 
                                                            objectFields[5], objectFields[6], gender, stringToAcademicTitle(objectFields[11]), 
                                                            stringToDepartment(objectFields[12]));
            m_entities.push_back(std::move(proff));
        }
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

std::vector<std::unique_ptr<Entity>> UniversityDatabase::findEntitiesByLastname(const std::string & lastname)
{
    /* Return vector because there is a possibility to exist several entities with the same lastname */
    std::vector<std::unique_ptr<Entity>> foundEntities;
    for(const auto & ent : m_entities)
    {
        if(ent->getLastname() == lastname)
        {
            foundEntities.push_back(ent->clone());
        }
    }

    return foundEntities;
}

std::unique_ptr<Entity> UniversityDatabase::findEntityByPesel(const std::string & pesel)
{
    auto it = std::find_if(m_entities.begin(), m_entities.end(),
                            [&pesel](const std::unique_ptr<Entity> & st){return st->getPesel() == pesel;});

    if (it == m_entities.end())
    {
        throw std::runtime_error("Entity with the given PESEL not found.");
    }

    return (*it)->clone();
}

bool UniversityDatabase::modifyEntityByPesel(const std::string & pesel, std::unique_ptr<Entity> new_ent)
{
    auto it = std::find_if(m_entities.begin(), m_entities.end(),
                            [&pesel](const std::unique_ptr<Entity> & st){return st->getPesel() == pesel;});

    if (it != m_entities.end())
    {
        *it = std::move(new_ent);
        this->saveAllEntitiesToCSV();
        return true;
    }
    else
    {
        return false;
    }
}

void UniversityDatabase::sortEntities(SortOrder order)
{
    switch(order)
    {
        case SORT_BY_LASTNAME_A_TO_Z:
        {
            std::sort(m_entities.begin(), m_entities.end(), 
                [](const std::unique_ptr<Entity>& a, const std::unique_ptr<Entity>& b){return a->getLastname() < b->getLastname();});
            break;
        }
        case SORT_BY_LASTNAME_Z_TO_A:
        {
            std::sort(m_entities.begin(), m_entities.end(),
                [](const std::unique_ptr<Entity>& a, const std::unique_ptr<Entity>& b){return a->getLastname() > b->getLastname();});
            break;
        }
        case SORT_BY_INDEX_ASCENDING:
        {
            std::sort(m_entities.begin(), m_entities.end(),
                [](const std::unique_ptr<Entity>& a, const std::unique_ptr<Entity>& b){return a->getIndex() < b->getIndex();});
            break;
        }
        case SORT_BY_INDEX_DESCENDING:
        {
            std::sort(m_entities.begin(), m_entities.end(),
                [](const std::unique_ptr<Entity>& a, const std::unique_ptr<Entity>& b){return a->getIndex() > b->getIndex();});
            break;
        }
        case SORT_BY_ENTITY_TYPE_A_TO_Z:
        {
            std::sort(m_entities.begin(), m_entities.end(),
                [](const std::unique_ptr<Entity>& a, const std::unique_ptr<Entity>& b){return a->getEntityType() > b->getEntityType();});
            break;
        }
        case SORT_BY_ENTITY_TYPE_Z_TO_A:
        {
            std::sort(m_entities.begin(), m_entities.end(),
                [](const std::unique_ptr<Entity>& a, const std::unique_ptr<Entity>& b){return a->getEntityType() < b->getEntityType();});
            break;
        }
        default:
        {
            std::sort(m_entities.begin(), m_entities.end(), 
                [](const std::unique_ptr<Entity>& a, const std::unique_ptr<Entity>& b){return a->getLastname() < b->getLastname();});
            break;
        }
            
    }
    
    this->saveAllEntitiesToCSV();
}

void UniversityDatabase::showEntities(void) const
{
    if (m_entities.empty()) return;


    for(const auto & ent : m_entities)
    {
        std::string info = ent->infoToString();
        std::cout << info;
    }
}

void UniversityDatabase::showEntitiesByEntityType(const EntityType & ent_type) const
{
    std::vector<Entity*> entForSelecedFldOfStd;

    for(const auto & ent : m_entities)
    {
        if(ent->getEntityType() == ent_type)
        {
            entForSelecedFldOfStd.push_back(ent.get());
        }
    }

    if(entForSelecedFldOfStd.empty()) return;

    for(const auto & ent : entForSelecedFldOfStd)
    {
        std::string info = ent->infoToString();
        std::cout << info;
    }
}

std::set<EntityType> UniversityDatabase::getEntityTypes(void) const
{
    std::set<EntityType> entity_types;

    if (m_entities.empty()) {
        std::cout << "Entity database is empty." << std::endl;
        return entity_types;
    }

    for(const auto & ent : m_entities)
    {
        entity_types.insert(ent->getEntityType());
    }
    
    return entity_types;
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

