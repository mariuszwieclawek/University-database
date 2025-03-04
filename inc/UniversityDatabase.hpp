#pragma once
#include <fstream>
#include <set>
#include <vector>
#include <memory>
#include <optional>
#include "Entity.hpp"

class UniversityDatabase
{
private:
    std::vector<std::unique_ptr<Entity>> m_entities;
    const std::string m_entitiesFilename = "../database/entities.csv";
    std::fstream m_file;

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
    std::vector<std::unique_ptr<Entity>> findEntitiesByLastname(const std::string & lastname);
    std::unique_ptr<Entity> findEntityByPesel(const std::string & pesel);
    bool modifyEntityByPesel(const std::string & pesel, std::unique_ptr<Entity> new_ent);
    void sortEntities(SortOrder order);

    std::set<EntityType> getEntityTypes(void) const;
    void showEntities(void) const;
    void showEntitiesByEntityType(const EntityType & ent_type) const;
};