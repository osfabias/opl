cmake_minimum_required(VERSION 3.16)

project(OPL VERSION 0.0.1 LANGUAGES C)

set(OPL_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_C_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# check if OPL is building as a standalone project
string(COMPARE EQUAL ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR} OPL_STANDALONE)

option(OPL_BUILD_TESTS "Build tests." ${OPL_STANDALONE})
option(OPL_BUILD_EXAMPLES "Build example programms." ${OPL_STANDALONE})

message(STATUS "OPL_BUILD_TESTS: ${OPL_BUILD_TESTS}")
message(STATUS "OPL_BUILD_EXAMPLES: ${OPL_BUILD_EXAMPLES}")

add_subdirectory(src)

if (OPL_BUILD_TESTS)
  add_subdirectory(tests)
endif()

if (OPL_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()
