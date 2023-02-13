cmake_minimum_required(VERSION 3.16)
project(tetris)

# Use the package PkgConfig to detect GTK+ headers/library files
find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)

# add GTKMM
link_directories(${GTKMM_LIBRARIES})
include_directories(${GTKMM_INCLUDE_DIRS})
add_definitions(${GTKMM_CFLAGS_OTHER})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread" )

add_subdirectory(src)

# link GTKMM libs
target_link_libraries(tetris ${CMAKE_THREAD_LIBS_INIT} ${GTKMM_LIBRARIES} )


