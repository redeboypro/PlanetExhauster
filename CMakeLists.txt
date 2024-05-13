cmake_minimum_required(VERSION 3.28)
project(PlanetExhauster)

set(CMAKE_CXX_STANDARD 23)

add_executable(PlanetExhauster main.cpp
        GLAPI.cpp
        GLAPI.h
        Window.cpp
        Window.h
        Math/Vector3D.h
        Math/Vector.h
        Math/Matrix.h
        Math/Matrix4x4.h
)

target_link_libraries(PlanetExhauster opengl32)