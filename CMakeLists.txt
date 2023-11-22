cmake_minimum_required (VERSION 3.1)
message("verson is ok")

project (demo)

include_directories (${CMAKE_CURRENT_SOURCE_DIR}/include)
message("headfile directories is setted")

link_directories (${CMAKE_CURRENT_SOURCE_DIR}/lib)
message("lib directories is setted")

aux_source_directory ( ${CMAKE_CURRENT_SOURCE_DIR}/src MY_SOURCES)
message("source directories is setted")

add_executable (test4acados  ${MY_SOURCES})
message("executable set is ok")

target_link_libraries (test4acados acados blasfeo hpipm m)
message("libraries is ok")

set (EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)
