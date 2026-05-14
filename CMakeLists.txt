cmake_minimum_required(VERSION 4.2)

project(NTRU LANGUAGES CXX)

set(ProjectName ntru)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES
    src/*.cpp
)

add_executable(${ProjectName}
    main.cpp
    ${SOURCES}
)

target_include_directories(${ProjectName} PRIVATE
    ${PROJECT_SOURCE_DIR}/hdrs
)
