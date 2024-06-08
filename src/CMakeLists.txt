# target setup
file(GLOB_RECURSE OGE_FRONTED_SOURCE_FILES "frontend/*.c")
add_library(opl ${OGE_FRONTED_SOURCE_FILES})
target_include_directories(opl PUBLIC ${OPL_SOURCE_DIR}/include)

if(APPLE)
  target_compile_definitions(opl PUBLIC _OPL_ENABLE_COCOA)
  message(STATUS "OPL: Cocoa platform enabled")
endif()

if(WIN32)
  target_compile_definitions(opl PUBLIC _OPL_ENABLE_WIN32)
  message(STATUS "OPL: Win32 platform enabled")
endif()
