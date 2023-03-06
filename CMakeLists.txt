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

add_executable(tetris src/main.cpp

        src/ui/MainWindow.h src/ui/MainWindow.cpp
        src/ui/graphicmatrix.h src/ui/graphicmatrix.cpp
        src/ui/leaderboard.h src/ui/leaderboard.cpp

        src/matrix.h src/game.h src/game.cpp

        src/multiplayer/server.cpp src/multiplayer/server.h
        src/multiplayer/client.cpp src/multiplayer/client.h
        src/multiplayer/communicator.cpp src/multiplayer/communicator.h

        src/multiplayer/messages/player.cpp src/multiplayer/messages/player.h
        src/multiplayer/messages/getplayerdata.cpp src/multiplayer/messages/getplayerdata.h
        src/multiplayer/messages/disconnect.cpp src/multiplayer/messages/disconnect.h
        src/multiplayer/messages/messageable.cpp src/multiplayer/messages/messageable.h
        src/multiplayer/messages/gamestart.cpp src/multiplayer/messages/gamestart.h)

# link GTKMM libs
target_link_libraries(tetris ${CMAKE_THREAD_LIBS_INIT} ${GTKMM_LIBRARIES} )


