cmake_minimum_required(VERSION 3.20)
project(main_project C)

enable_language(C)
enable_language(CXX)


set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

add_subdirectory(sources)
include_directories(sources)

add_executable(${PROJECT_NAME} main.c)
target_link_libraries(${PROJECT_NAME} sources)
