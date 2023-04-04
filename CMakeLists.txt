cmake_minimum_required(VERSION 3.20)
project(ScenePort)

# Fetch dependencies
set(CEREAL_COMMIT 664d5cc4c2f1527f7490dbeb9704c0cf78b6cf80) # Version 1.3.2

include(FetchContent)

add_subdirectory(extern/cereal-no-boost)

include_directories(src/ extern/cereal-no-boost/include)
file(GLOB_RECURSE scene_port_src "src/*.cpp")

add_library(ScenePort ${scene_port_src})
target_link_libraries(ScenePort cereal)

# Testing framework
set(GTEST_COMMIT e2239ee6043f73722e7aa812a459f54a28552929) # Version 1.11.0
set(STB_COMMIT 3ecc60f25ae1391cf6434578ece782afa1458b5)

if(NOT SWITCH AND NOT ${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    FetchContent_Declare(googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG ${GTEST_COMMIT})

    set(GTEST_FORCE_SHARED_CRT ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    FetchContent_Declare(stb
            GIT_REPOSITORY https://github.com/nothings/stb
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
endif()

file(COPY res DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
