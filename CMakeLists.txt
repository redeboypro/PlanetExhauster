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
)

target_link_libraries(PlanetExhauster opengl32)

include_directories("D:\\glm-1.0.1-light\\glm")
target_link_libraries(PlanetExhauster glm)