cmake_minimum_required(VERSION 3.6)
project(Lost_in_Time)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic")

set(SOURCE_FILES
        main.cpp

        state/machine.h
        state/machine.cpp
        state/state.h
        state/stategame.cpp
        state/stategame.h
        state/statemainmenu.cpp
        state/statemainmenu.h
        state/statepause.h
        state/statepause.cpp
        state/teststate.cpp
        state/teststate.h
        state

        data/map.json
        data/tileset.png
        data/backgroundmainmenu.png
        data/ExitGame.png
        data/ExitGameSelected.png
        data/LoadGame.png
        data/LoadGameSelected.png
        data/NewGame.png
        data/NewGameSelected.png
        data

        Enemy

        Framework

        Interface

        Map/game.cpp
        Map/game.h
        Map/layer.cpp
        Map/layer.h
        Map/map.h
        Map/map.cpp
        Map/object.cpp
        Map/object.h
        Map/sprite.cpp
        Map/sprite.h
        Map

        Player/player.cpp
        Player/player.h
        Player

        Objects/testcollidableplatform.cpp
        Objects/testcollidableplatform.h
        Objects/gameobject.cpp
        Objects/gameobject.h
        Objects/playertest.cpp
        Objects/playertest.h
        Objects
        testapp.cpp
        testapp.h)

add_executable(Lost_in_Time ${SOURCE_FILES})

target_link_libraries(Lost_in_Time sfml-audio sfml-graphics sfml-window sfml-system jsoncpp)