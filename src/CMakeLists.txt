# target setup
add_library(opl STATIC ${OPL_SOURCE_DIR}/include/opl/opl.h
                        internal.h init.c
                        platform.h platform.c)
target_include_directories(opl PUBLIC ${OPL_SOURCE_DIR}/include)

if(APPLE)
  target_compile_definitions(opl PUBLIC _OPL_ENABLE_COCOA)
  message(STATUS "OPL: Cocoa platform enabled")
  target_sources(opl PUBLIC
                 init_cocoa.h init_cocoa.c
                 platform_cocoa.h platform_cocoa.c)
endif()

if(WIN32)
  target_compile_definitions(opl PUBLIC _OPL_ENABLE_WIN32)
  message(STATUS "OPL: Win32 platform enabled")
endif()
