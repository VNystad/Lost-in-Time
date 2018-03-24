cmake_minimum_required(VERSION 3.6)
project(Lost-in-Time)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic")

set(SOURCE_FILES
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
        Framework/Music.cpp
        Framework/Music.h
        Framework/Sounds.cpp
        Framework/Sounds.h

        Interface/deathscreen.cpp
        Interface/deathscreen.h
        Interface/Dialogue.cpp
        Interface/Dialogue.h
        Interface/health.cpp
        Interface/health.h
        Interface/highscore.cpp
        Interface/highscore.h

        Map/layer.cpp
        Map/layer.h
        Map/map.cpp
        Map/map.h
        Map/object.cpp
        Map/object.h
        Map/sprite.cpp
        Map/sprite.h
        Map/tile.h

        Objects/Items/Mace.cpp
        Objects/Items/Mace.h
        Objects/Items/item.cpp
        Objects/Items/item.h
        Objects/playerobject.cpp
        Objects/playerobject.h
        Objects/princessobject.cpp
        Objects/princessobject.h
        Objects/savedobject.cpp
        Objects/savedobject.h
        Objects/spawnpoint.cpp
        Objects/spawnpoint.h

        SaveFiles

        state/machine.cpp
        state/machine.h
        state/state.h
        state/stategame.cpp
        state/stategame.h
        state/stateloadgame.cpp
        state/stateloadgame.h
        state/statemainmenu.cpp
        state/statemainmenu.h

        main.cpp
        levelOne.cpp
        levelOne.h
        )

add_executable(Lost-in-Time ${SOURCE_FILES})

target_link_libraries(Lost-in-Time sfml-audio sfml-graphics sfml-window sfml-system jsoncpp)