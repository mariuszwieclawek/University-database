#pragma once
#include <fstream>
#include <set>
#include <vector>
#include "Entity.hpp"

class UniversityDatabase
{
private:
    std::vector<std::unique_ptr<Entity>> m_entities;
    const std::string m_entitiesFilename = "../database/entities.csv";
    std::fstream m_file;

    static bool compareByLastnameAtoZ(const std::unique_ptr<Entity>& a, const std::unique_ptr<Entity>& b);
    static bool compareByLastnameZtoA(const std::unique_ptr<Entity>& a, const std::unique_ptr<Entity>& b);
    static bool compareByIndexAscending(const std::unique_ptr<Entity>& a, const std::unique_ptr<Entity>& b);
    static bool compareByIndexDescending(const std::unique_ptr<Entity>& a, const std::unique_ptr<Entity>& b);
    static bool compareByEntityTypeAtoZ(const std::unique_ptr<Entity>& a, const std::unique_ptr<Entity>& b);
    static bool compareByEntityTypeZtoA(const std::unique_ptr<Entity>& a, const std::unique_ptr<Entity>& b);

    void appendToCSV(std::fstream& file, const std::string& data);
    bool isCSVFileEmpty(std::fstream& file);
    void readEntitiesFromCSV(std::fstream& file);
    void saveAllEntitiesToCSV(void);
public:

    enum SortOrder {
        SORT_BY_LASTNAME_A_TO_Z = 0,
        SORT_BY_LASTNAME_Z_TO_A = 1,
        SORT_BY_INDEX_ASCENDING = 2,
        SORT_BY_INDEX_DESCENDING = 3,
        SORT_BY_ENTITY_TYPE_A_TO_Z = 4,
        SORT_BY_ENTITY_TYPE_Z_TO_A = 5,
    };

    UniversityDatabase(void);
    ~UniversityDatabase(void);

    void addEntity(std::unique_ptr<Entity> entity);
    bool removeEntityByPesel(const std::string & pesel);
    std::vector<const Entity*> findEntitiesByLastname(const std::string & lastname);
    bool modifyEntityByPesel(const std::string & pesel);
    void sortEntities(SortOrder order);

    std::set<EntityType> getEntityTypes(void) const;
    void showEntities(void) const;
    void showEntitiesByEntityType(const EntityType & ent_type) const;
};