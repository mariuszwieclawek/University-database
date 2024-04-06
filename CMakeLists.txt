# Minimalna wersja CMake
cmake_minimum_required(VERSION 3.10)

# Nazwa projektu
project(StudentDatabase)

# Pliki źródłowe C++
set(CXX_SRCS
    src/main.cpp
)

# Budowanie pliku wykonywalnego
add_executable(${PROJECT_NAME}-app ${CXX_SRCS})




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

add_executable(${PROJECT_NAME}-ut src/tests.cpp)
target_link_libraries(${PROJECT_NAME}-ut GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}-ut)