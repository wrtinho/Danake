find_package(Threads)

add_definitions(-Wall -g -pedantic -ggdb -lpthread -lcppdb_sqlite3)

add_executable(Danake main.c)

add_library(resources resources.c)
add_library(routes routes.c)

target_link_libraries(Danake mongoose)
target_link_libraries(Danake sqlite3)
target_link_libraries(Danake routes)
target_link_libraries(Danake resources)

target_link_libraries (Danake ${CMAKE_THREAD_LIBS_INIT})

set(CMAKE_C_FLAGS "-std=c99")