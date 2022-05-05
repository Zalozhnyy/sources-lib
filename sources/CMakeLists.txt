
cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 14)

project(sources)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(jsoncpp REQUIRED)

get_target_property(JSON_INC_PATH jsoncpp_static INTERFACE_INCLUDE_DIRECTORIES)
include_directories(${JSON_INC_PATH})
include_directories("../GridStudio/data")


file(GLOB SORCE_FILES
${PROJECT_SOURCE_DIR}/*.cpp
${PROJECT_SOURCE_DIR}/*.h)

add_library(${PROJECT_NAME} STATIC ${SORCE_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE jsoncpp_static)
target_link_libraries(${PROJECT_NAME} PRIVATE Data)



set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)
