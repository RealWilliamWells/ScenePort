cmake_minimum_required(VERSION 3.20)
project(scene-data)

file(GLOB_RECURSE SRCS "src/*.cpp")
include_directories(src/)

add_library(scene-data ${SRCS})

# Fetch dependencies
set(GTEST_COMMIT e2239ee6043f73722e7aa812a459f54a28552929) # Version 1.11.0

include(FetchContent)

FetchContent_Declare(googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG ${GTEST_COMMIT})

set(GTEST_FORCE_SHARED_CRT ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Testing framework
include_directories(tests/)

enable_testing()

file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/tests/*.cpp)
add_executable(${PROJECT_NAME}_tests ${TEST_SRC_FILES})

target_link_libraries(${PROJECT_NAME}_tests
     gtest_main
     ${PROJECT_NAME})

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_tests)