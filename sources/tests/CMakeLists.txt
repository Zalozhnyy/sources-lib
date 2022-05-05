
project(tests)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

find_package(Catch2 REQUIRED)
find_package(jsoncpp REQUIRED)

include_directories(../)
include_directories("../../GridStudio/data")


# Make test executables
#include(CTest)
include(Catch)

# code coverage using gcov
if (UNIX)
    set(CMAKE_EXE_LINKER_FLAGS "--coverage")
endif()

file(GLOB SORCE_FILES
        ${PROJECT_SOURCE_DIR}/*.cpp
        ${PROJECT_SOURCE_DIR}/*.h)


add_executable(tests ${SORCE_FILES})
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
target_link_libraries(tests PRIVATE sources)
#set_property(TARGET reading_test PROPERTY FOLDER "Data Tests")
#catch_discover_tests(
#        base64_test
#        REPORTER junit
#        OUTPUT_DIR ../
#        OUTPUT_SUFFIX .xml
#)

