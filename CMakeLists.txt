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
)

target_link_libraries(PlanetExhauster opengl32)

include_directories(D:/glm-1.0.1-light/glm)

target_link_libraries(PlanetExhauster -static)