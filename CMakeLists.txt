cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_COVERAGE "Build coverage" OFF)

set(
        HUNTER_CACHE_SERVERS
        "https://github.com/bmstu-iu8-cpp-sem-3/hunter-cache"
        CACHE STRING "Default cache server"
)

include("cmake/HunterGate.cmake")

HunterGate(
        URL "https://github.com/cpp-pm/hunter/archive/v0.23.271.tar.gz"
        SHA1 "2d6686024529b471e0cc3a4fc07d4d64b62a53ee"
)


# TODO: rename project and delete this comment
project(suggestion)
string(APPEND CMAKE_CXX_FLAGS " -pedantic -Werror -Wall -Wextra")
string(APPEND CMAKE_CXX_FLAGS " -Wno-unused-command-line-argument")
string(APPEND CMAKE_CXX_FLAGS " -Wshadow -Wnon-virtual-dtor")

hunter_add_package(Beast)
find_package(Beast CONFIG REQUIRED)
hunter_add_package(Boost COMPONENTS  thread filesystem)
find_package(Boost CONFIG REQUIRED thread filesystem)
find_package(Threads)
hunter_add_package(GTest)
find_package(GTest CONFIG REQUIRED)
hunter_add_package(nlohmann_json)
find_package(nlohmann_json CONFIG REQUIRED)

add_executable(tests
        # TODO: enum your files and delete this comment
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/JsonStorage.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/suggestions.cpp
        #${CMAKE_CURRENT_SOURCE_DIR}/sources/source.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/test.cpp
        )

# TODO: change template word to project name and delete this comment

target_include_directories(tests
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
        )
# TODO: change template word to project name and delete this comment
target_link_libraries(tests
        Beast::Beast
        Boost::filesystem
        Boost::thread
        GTest::gmock_main
        nlohmann_json::nlohmann_json
        )
        
enable_testing()
add_test(NAME unit_tests COMMAND tests)

if (BUILD_COVERAGE)
  function(ENABLE_PROJECT_COVERAGE PROJECT)
    target_compile_options(${PROJECT} INTERFACE -O0 -g --coverage)
    if (CMAKE_VERSION VERSION_GREATER_EQUAL 3.13)
      target_link_options(${PROJECT} INTERFACE --coverage)
    else()
      target_link_libraries(${PROJECT} INTERFACE --coverage)
    endif()
  endfunction()

  set(ENABLE_COVERAGE ON CACHE BOOL "Enable coverage build." FORCE)
  list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
  find_package(codecov)
  enable_project_coverage(template)
  enable_project_coverage(tests)
  list(APPEND LCOV_REMOVE_PATTERNS "'${PROJECT_SOURCE_DIR}/tests/*'")
  coverage_evaluate()
endif()
