add_executable(window-creation window-creation.c)
target_link_libraries(window-creation PRIVATE opl)

add_executable(alert alert.c)
target_link_libraries(alert PRIVATE opl)

add_executable(console console.c)
target_link_libraries(console PRIVATE opl)

add_executable(files files.c)
target_link_libraries(files PRIVATE opl)

add_executable(threads threads.c)
target_link_libraries(threads PRIVATE opl)
