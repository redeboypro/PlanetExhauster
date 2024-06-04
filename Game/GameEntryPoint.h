
//
// Created by redeb on 31.05.2024.
//

#ifndef GAMEENTRYPOINT_H
#define GAMEENTRYPOINT_H
#include "PlayerController.h"
#include "../AssetManager.h"
#include "../GUI/GUI.h"

#include "Map/Obstacle.h"
#include "Map/ObstaclesGrid.h"
#include "Map/ObstaclesGenerator.h"

#define CLEAR_COLOR 0.1F, 0.6F, 0.8F, 1.0F

#define WORLD_VERTEX_SHADER_FILENAME "mesh_vert.glsl"
#define WORLD_FRAGMENT_SHADER_FILENAME "mesh_frag.glsl"

#define GUI_VERTEX_SHADER_FILENAME "gui_vert.glsl"
#define GUI_FRAGMENT_SHADER_FILENAME "gui_frag.glsl"

#define CLIFFS_TEXTURE_FILEPATH "cliffs.pet"

#define LANDSCAPE_MESH_FILEPATH "landscape.pem"
#define LANDSCAPE_COLLISIONMESH_FILEPATH "landscape.pecm"

#define PISTOL_MESH_FILEPATH "pistol.pem"
#define PISTOL_TEXTURE_FILEPATH "pistol.pet"
#define PISTOL_LAYER "Pistol"

#define GAME_TITLE "Planet Exhauster"
#define GAME_WIN_W 800
#define GAME_WIN_H 600

#define GAME_CAMERA_FOV 60.0F
#define GAME_CAMERA_NEAR 0.1F
#define GAME_CAMERA_FAR 100.0F

class GameEntryPoint {
    Window* m_window;
    Input* m_input;

    World* m_world;
    GUI* m_gui;

    AssetManager* m_assetManager;

    Shader* m_worldShader;
    Shader* m_guiShader;

    //Game objects in the root:
    PlayerController* m_player;

    Map::ObstaclesGenerator* m_obstaclesGenerator;
    Map::ObstaclesGrid* m_obstaclesGrid;
    std::vector<Map::Obstacle> m_cliffsPrefabs;

    Rigidbody* m_landscape;

    static std::string readFile(const std::string& fileName);
public:
    GameEntryPoint();
    ~GameEntryPoint();

    void update(GLfloat deltaTime) const;
};



#endif //GAMEENTRYPOINT_H
