cmake_minimum_required(VERSION 3.6)
project(Lost-in-Time)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic")

set(SOURCE_FILES
        cmake-build-debug
        data

        Enemy/AI.cpp
        Enemy/AI.h
        Enemy/AIEnemies.cpp
        Enemy/AIEnemies.h

        Framework/animation.cpp
        Framework/animation.h
        Framework/Camera.h
        Framework/config.h
        Framework/font.cpp
        Framework/font.h
        Framework/physics.cpp
        Framework/physics.h

        Interface/deathscreen.cpp
        Interface/deathscreen.h
        Interface/health.cpp
        Interface/health.h
        Interface/timer.cpp
        Interface/timer.h

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

        State/stateloadgame.cpp
        State/stateloadgame.h
        state/machine.cpp
        state/machine.h
        state/state.h
        state/stategame.cpp
        state/stategame.h
        state/statemainmenu.cpp
        state/statemainmenu.h

        main.cpp
        testapp.cpp
        testapp.h


        Framework/music.cpp Framework/music.h Objects/savedobject.cpp Objects/savedobject.h)

add_executable(Lost-in-Time ${SOURCE_FILES})

target_link_libraries(Lost-in-Time sfml-audio sfml-graphics sfml-window sfml-system jsoncpp)