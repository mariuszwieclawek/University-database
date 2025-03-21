#pragma once

enum class EntityType 
{
    Student,
    Professor,
    Admin,
    Staff,
    Unknown,
};

enum class Gender {
    Male,
    Female,
    Default
};


enum class AcademicTitle 
{
    AssociateProfessor,
    Professor,
    TitularProfessor,
    DoctorHabilitatus,
};


enum class Department
{
    ComputerScience,
    ElectronicsAndTelecommunications,
    Architecture,
    Mathematics,
    Physics,
    Chemistry,
    Medicine,
    Pharmacy,
    Psychology,
};

enum class FieldOfStudy 
{
    ComputerScience,
    ElectricalEngineering,
    MechanicalEngineering,
    CivilEngineering,
    Architecture,
    Medicine,
    Law,
    Business,
    Psychology,
    Philosophy,
    Mathematics,
    Physics,
    Default
};

enum class Subject 
{
    Analytics,
    Algebra,
    DataStructures,
    Math,
    Economics,
    Astrophysics,
    Physics,
    Philosophy,
    Psychology,
    LiteraryAnalysis,
    StatisticalAnalysis,
    SoftwareEngineering,
    Default
};
