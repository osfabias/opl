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

# ~ detecting standalone build
set(OPL_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
string(COMPARE EQUAL "${CMAKE_CURRENT_SOURCE_DIR}" "${OPL_SOURCE_DIR}" OPL_STANDALONE)

# ~ defining options
option(OPL_BUILD_EXAMPLES "Build the opl example programs" ${OPL_STANDALONE})

# ~ printing info
message(STATUS "==== OPL info ====")
message(STATUS "lib type: static")
message(STATUS "version:  ${OPL_VERSION}")
message(STATUS "OPL_BUILD_EXAMPLES:  ${OPL_BUILD_EXAMPLES}")


#####################################################
#                    target setup                   #
#####################################################
# ~ finding required packages
find_package(Vulkan REQUIRED)

# ~ target set up
add_library(opl STATIC ./src/null.c)

target_link_libraries(opl PUBLIC Vulkan::Vulkan)
target_include_directories(opl PUBLIC include)

# ~ platform-specific source files
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
  target_sources(opl PRIVATE
    ./src/win32-platform.c
    ./src/posix-time.c
    ./src/posix-memory.c
  )
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
  find_package(X11 REQUIRED)

  target_link_libraries(opl PUBLIC ${X11_LIBRARIES})

  target_sources(opl PRIVATE
    ./src/x11-platform.c
    ./src/posix-file.c
    ./src/posix-time.c
    ./src/posix-thread.c
    ./src/posix-memory.c
    ./src/posix-console.c
  )
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin") # MACOS
  find_library(COCOA_LIBRARY Cocoa)
  find_library(QUARTZ_LIBRARY QuartzCore)
  target_link_libraries(opl PUBLIC
    ${COCOA_LIBRARY}
    ${QUARTZ_LIBRARY}
  )

  target_sources(opl PRIVATE
    ./src/cocoa-platform.m
    ./src/posix-file.c
    ./src/cocoa-time.c
    ./src/posix-thread.c
    ./src/posix-memory.c
    ./src/posix-console.c
  )
endif()

# ~ example programm
if (OPL_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()
