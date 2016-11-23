cmake_minimum_required(VERSION 3.6)
project(Lost-in-Time)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic")

set(SOURCE_FILES
        main.cpp
        testapp.h
        testapp.cpp

        data/Character-Animation/characterdeath.png
        data/Character-Animation/characteridle.png
        data/Character-Animation/characterjump.png
        data/Character-Animation/characterjumpflipped.png
        data/Character-Animation/charactermove.png
        data/Character-Animation/charactermoveflipped.png

        data/Font/BitMapFont.TTF

        data/HUD/Health/Lost-in-Time_health-bar-red.png
        data/HUD/Health/Lost-in-Time_health-bar-green.png
        data/HUD/Health/Lost-in-Time_health-bar-border.png

        data/main-menu/backgroundmainmenu.png
        data/main-menu/ExitGame.png
        data/main-menu/ExitGameSelected.png
        data/main-menu/LoadGame.png
        data/main-menu/LoadGameSelected.png
        data/main-menu/NewGame.png
        data/main-menu/NewGameSelected.png

        data/map.json
        data/tileset.png

        Framework/animation.cpp
        Framework/animation.h
        Framework/Camera.h
        Framework/config.h
        Framework/physics.cpp
        Framework/physics.h
        Framework/font.cpp
        Framework/font.h

        Interface/health.cpp
        Interface/health.h
        Interface/deathscreen.cpp
        Interface/deathscreen.h

        Map/layer.cpp
        Map/layer.h
        Map/map.cpp
        Map/map.h
        Map/object.cpp
        Map/object.h
        Map/sprite.cpp
        Map/sprite.h
        Map/tile.h

        Objects/playertest.cpp
        Objects/playertest.h

        state/loadgamestate.cpp
        state/loadgamestate.h
        state/machine.cpp
        state/machine.h
        state/state.h
        state/stategame.cpp
        state/stategame.h
        state/statemainmenu.cpp
        state/statemainmenu.h
        state/statepause.cpp
        state/statepause.h
        )

add_executable(Lost-in-Time ${SOURCE_FILES})

target_link_libraries(Lost-in-Time sfml-audio sfml-graphics sfml-window sfml-system jsoncpp)