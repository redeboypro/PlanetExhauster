cmake_minimum_required(VERSION 3.28)
project(PlanetExhauster)

set(CMAKE_CXX_STANDARD 23)

add_executable(PlanetExhauster main.cpp
        GLAPI.cpp
        GLAPI.h
)
