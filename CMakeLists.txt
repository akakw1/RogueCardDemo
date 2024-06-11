cmake_minimum_required(VERSION 3.28)

project(server)

set(CMAKE_CXX_STANDARD 11)

aux_source_directory(src SRC_LIST)

add_library(jsoncpp STATIC IMPORTED)
set_property(TARGET jsoncpp PROPERTY IMPORTED_LOCATION ./lib/libjsoncpp.a)

add_executable(main main.cpp ${SRC_LIST})

include_directories (/usr/include/mysql)
target_link_libraries(main jsoncpp mysqlclient)