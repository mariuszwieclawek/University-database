# Minimalna wersja CMake
cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)

# Nazwa projektu
project(UniversityDatabase)

# Pliki źródłowe C++
set(CXX_SRCS
    src/Main.cpp
    src/UniversityDatabase.cpp
    src/Student.cpp
    src/CommandLineInterface.cpp
)

# Budowanie pliku wykonywalnego
add_executable(${PROJECT_NAME}-app ${CXX_SRCS})

# Dolacz pliki nagłówkowe
target_include_directories(${PROJECT_NAME}-app PUBLIC
    inc
)


########################### Unit Test GTEST Framework ###########################
# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(${PROJECT_NAME}-ut src/Tests.cpp)
target_link_libraries(${PROJECT_NAME}-ut GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}-ut)