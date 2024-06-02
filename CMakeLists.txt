cmake_minimum_required(VERSION 3.28)
project(PlanetExhauster)

set(CMAKE_CXX_STANDARD 23)

add_executable(PlanetExhauster main.cpp
        GLAPI.cpp
        GLAPI.h
        Window.cpp
        Window.h
        Mesh.h
        Texture.h
        Assert.h
        Shader.h
        World/Entity.cpp
        World/Entity.h
        World/World.cpp
        World/World.h
        World/Physics/Collider.cpp
        World/Physics/Collider.h
        World/Physics/GJK.cpp
        World/Physics/GJK.h
        World/Physics/Simplex.cpp
        World/Physics/Simplex.h
        World/Physics/EPA.cpp
        World/Physics/EPA.h
        World/Physics/Collision.h
        World/Physics/Rigidbody.cpp
        World/Physics/Rigidbody.h
        Input.cpp
        Input.h
        AssetManager.cpp
        AssetManager.h
        GUI/Font.cpp
        GUI/Font.h
        GUI/GUI.cpp
        GUI/GUI.h
        Primitives.h
        Game/GameEntryPoint.cpp
        Game/GameEntryPoint.h
        Game/Map/Obstacle.cpp Game/Map/Obstacle.h Game/Map/ObstaclesGrid.cpp Game/Map/ObstaclesGrid.h
        Game/Map/ObstaclesGenerator.cpp
        Game/Map/ObstaclesGenerator.h)

target_link_libraries(PlanetExhauster opengl32)

include_directories(external/glm-1.0.1-light/glm)

target_link_libraries(PlanetExhauster -static)