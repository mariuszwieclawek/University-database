#include <sstream>
#include <ctime>
#include <iomanip>

enum class EntityType 
{
    Student,
    Professor,
    Admin,
    Staff
};

enum class Gender {
    Male,
    Female,
    Default
};

Gender stringToGender(const std::string& str);
EntityType stringToEntityType(const std::string& str);
std::tm stringToTm(const std::string& dateStr, const std::string& format);
std::string TmToString(const std::tm & tmdate, const std::string& format);

std::ostream& operator<<(std::ostream & os, const Gender & gender);
std::istream& operator>>(std::istream & is, Gender & gender);
std::ostream& operator<<(std::ostream & os, const EntityType & entitytype);
std::istream& operator>>(std::istream & is, EntityType & entitytype);
