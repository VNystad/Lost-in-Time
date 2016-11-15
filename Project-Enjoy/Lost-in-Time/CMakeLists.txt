cmake_minimum_required(VERSION 3.6)
project(Lost-in-Time)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic")

set(SOURCE_FILES
        main.cpp
        testapp.cpp
        testapp.h

        state
        state/state.h
        state/machine.cpp
        state/machine.h
        state/loadgamestate.cpp
        state/loadgamestate.h
        state/stategame.cpp
        state/stategame.h
        state/statemainmenu.cpp
        state/statemainmenu.h
        state/statepause.h
        state/statepause.cpp
        state/teststate.cpp
        state/teststate.h

        Map
        Map/layer.cpp
        Map/layer.h
        Map/map.cpp
        Map/map.h
        Map/object.cpp
        Map/object.h
        Map/sprite.cpp
        Map/sprite.h
        Map/tile.h

        Player
        Player/player.cpp
        Player/player.h

        Enemy

        Framework
        Framework/config.h
        Framework/physics.cpp
        Framework/physics.h

        Interface

        Objects
        Objects/playertest.cpp
        Objects/playertest.h

        data
        data/map.json
        data/tileset.png
        data/Character-Animation
        data/Character-Animation/characterdeath.png
        data/Character-Animation/characteridle.png
        data/Character-Animation/characterjump.png
        data/Character-Animation/characterjumpflipped.png
        data/Character-Animation/charactermove.png
        data/Character-Animation/charactermoveflipped.png
        data/main-menu/backgroundmainmenu.png
        data/main-menu/ExitGame.png
        data/main-menu/ExitGameSelected.png
        data/main-menu/LoadGame.png
        data/main-menu/LoadGameSelected.png
        data/main-menu/NewGame.png
        data/main-menu/NewGameSelected.png

        Framework/Camera.h)

add_executable(Lost-in-Time ${SOURCE_FILES})

target_link_libraries(Lost-in-Time sfml-audio sfml-graphics sfml-window sfml-system jsoncpp)