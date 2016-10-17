cmake_minimum_required(VERSION 3.6)
project(Lost_in_Time)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic")

set(SOURCE_FILES main.cpp)
add_executable(Lost_in_Time ${SOURCE_FILES})

target_link_libraries(Lost_in_Time sfml-audio sfml-graphics sfml-window sfml-system jsoncpp)