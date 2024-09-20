cmake_minimum_required(VERSION 3.5)
project(scanner)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(nlohmann_json 3.11.3 REQUIRED)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(scanner main.cpp ${SOURCES})
target_link_libraries(scanner PRIVATE nlohmann_json::nlohmann_json)
