cmake_minimum_required(VERSION 3.20)
project(scene-data)

file(GLOB_RECURSE SRCS "src/*.cpp")

# Fetch dependencies
set(CEREAL_COMMIT ebef1e929807629befafbb2918ea1a08c7194554) # Version 1.3.2

include(FetchContent)

FetchContent_Declare(cereal
        GIT_REPOSITORY https://github.com/USCiLab/cereal.git
        GIT_TAG ${CEREAL_COMMIT})
FetchContent_MakeAvailable(cereal)
FetchContent_GetProperties(cereal SOURCE_DIR CEREAL_SOURCE_DIR)

include_directories(src/ ${CEREAL_SOURCE_DIR}/include)

add_library(scene-data ${SRCS})


# Testing framework
set(GTEST_COMMIT e2239ee6043f73722e7aa812a459f54a28552929) # Version 1.11.0
set(STB_COMMIT 3ecc60f25ae1391cf6434578ece782afa1458b5)

FetchContent_Declare(googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG ${GTEST_COMMIT})

set(GTEST_FORCE_SHARED_CRT ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(stb
        GIT_REPOSITORY git@github.com:nothings/stb.git
        GIT_TAG ${STB_COMMIT})
FetchContent_MakeAvailable(stb)
FetchContent_GetProperties(stb SOURCE_DIR STB_SOURCE_DIR)

include_directories(tests/ ${STB_SOURCE_DIR})

enable_testing()

file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/tests/*.cpp)
add_executable(${PROJECT_NAME}_tests ${TEST_SRC_FILES})

target_link_libraries(${PROJECT_NAME}_tests
     gtest_main
     ${PROJECT_NAME})

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_tests)

file(COPY res DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
