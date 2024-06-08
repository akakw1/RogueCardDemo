cmake_minimum_required(VERSION 3.29)

project(server)

set(CMAKE_CXX_STANDARD 11)

aux_source_directory(src SRC_LIST)

add_executable(main main.cpp ${SRC_LIST})

include_directories (/usr/include/mysql)