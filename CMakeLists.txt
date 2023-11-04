cmake_minimum_required(VERSION 3.20..3.30)
project(AoC23)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wpedantic -Wunused")

set(COMMON_INCLUDES
    ${PROJECT_SOURCE_DIR}/src/include 
    ${PROJECT_SOURCE_DIR}/libs)

set(HEADERS
    src/days/include/day01.hpp
    src/days/Puzzle.hpp
    src/dataset.hpp
    src/args.hpp
    src/advent.hpp
    src/utilities.hpp)

file(GLOB DAY_SOURCES "src/days/*.cpp")

set(SOURCES
    src/main.cpp
    ${DAY_SOURCES})

include_directories(${COMMON_INCLUDES})

add_library(${PROJECT_NAME}_lib ${SOURCES} ${HEADERS})

add_executable(${PROJECT_NAME} src/main.cpp ${HEADERS})
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_lib)

target_include_directories(${PROJECT_NAME}_lib
    PRIVATE
    include)
