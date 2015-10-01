cmake_minimum_required(VERSION 2.6)

project(Danake)

add_library(mongoose mongoose.c)
add_library(sqlite3 sqlite3.c)

find_package(Threads)

add_definitions(-Wall -g -pedantic -ggdb -lpthread -lcppdb_sqlite3)

add_executable(Danake main.c)

target_link_libraries(Danake mongoose)
target_link_libraries(Danake sqlite3)

target_link_libraries (Danake ${CMAKE_THREAD_LIBS_INIT})
