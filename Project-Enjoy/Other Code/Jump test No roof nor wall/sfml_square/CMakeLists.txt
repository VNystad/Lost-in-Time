cmake_minimum_required(VERSION 3.6)
project(sfml_square)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -Wall -pedantic")

set(SOURCE_FILES main.cpp square.cpp square.h config.h app.cpp app.h platform.cpp platform.h)
add_executable(sfml_square ${SOURCE_FILES})
target_link_libraries(sfml_square sfml-graphics sfml-window sfml-system)