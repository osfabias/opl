cmake_minimum_required(VERSION 3.16)

#####################################################
#                   project setup                   #
#####################################################
# ~ version
set(OPL_VERSION_MAJOR 0)
set(OPL_VERSION_MINOR 0)
set(OPL_VERSION_PATCH 1)
set(OPL_VERSION ${OPL_VERSION_MAJOR}.${OPL_VERSION_MINOR}.${OPL_VERSION_PATCH})

# ~ project creation
project(opl VERSION ${OPL_VERSION} LANGUAGES C)

# ~ setting cmake variables
set(CMAKE_C_STANDARD 99)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # for clangd

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# ~ printing info
message(STATUS "==== OPL info ====")
message(STATUS "lib type: static")
message(STATUS "version:  ${OPL_VERSION}")

# ~ detecting standalone build
string(COMPARE EQUAL "${CMAKE_CURRENT_SOURCE_DIR}" "${OPL_SOURCE_DIR}" OPL_STANDALONE)

# ~ defining options
option(OPL_BUILD_EXAMPLE "Build the opl example program" ${OPL_STANDALONE})

#####################################################
#                    target setup                   #
#####################################################
# ~ finding required packages
find_package(Vulkan REQUIRED)

# ~ target set up
add_library(opl STATIC
  ./src/opl.c
)

target_link_libraries(opl PUBLIC Vulkan::Vulkan)
target_include_directories(opl PUBLIC include)

# ~ platform-specific source files
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
  message(FATAL_ERROR "Windows platform not implemented.")
  # Add source files here instead of "message()" call
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
  message(FATAL_ERROR "Linux platform not implemented.")
  # Add source files here instead of "message()" call
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin") # MACOS
  target_compile_definitions(opl PRIVATE OPL_PLATFORM_MACOS)

  find_library(COCOA_LIBRARY Cocoa)
  find_library(QUARTZ_LIBRARY QuartzCore)
  target_link_libraries(opl PUBLIC
    ${COCOA_LIBRARY}
    ${QUARTZ_LIBRARY}
  )

  target_sources(opl PRIVATE
    ./src/cocoa-platform.m
    ./src/cocoa-time.c
    ./src/posix-memory.c
    ./src/posix-thread.c
  )
endif()

# ~ example programm
if (OPL_BUILD_EXAMPLE)
  add_subdirectory(example)
endif()
