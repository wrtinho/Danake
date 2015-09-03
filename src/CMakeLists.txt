find_package(Threads)

add_definitions(-Wall -g -pedantic -ggdb -lpthread -lcppdb_sqlite3)

add_executable(Danake main.c)

target_link_libraries(Danake mongoose)

target_link_libraries(Danake sqlite3)

target_link_libraries(Danake aritmetica)

target_link_libraries (Danake ${CMAKE_THREAD_LIBS_INIT})

