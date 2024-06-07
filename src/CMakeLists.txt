message(WARNING "OPL library not implemented.")

add_library(opl null.c)
target_include_directories(opl PUBLIC ${OPL_SOURCE_DIR}/include)
