cmake_minimum_required(VERSION 3.16)
project(main_project CXX)

enable_language(C)
enable_language(CXX)


set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

add_subdirectory(sources)
add_subdirectory(GridStudio/data)

include_directories(sources)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} sources)
