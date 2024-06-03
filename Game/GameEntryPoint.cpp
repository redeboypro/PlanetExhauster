//
// Created by redeb on 31.05.2024.
//

#include "GameEntryPoint.h"

std::string GameEntryPoint::readFile(const std::string &fileName) {
    std::ifstream file(fileName);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << fileName << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

GameEntryPoint::GameEntryPoint(): m_assetManager(new AssetManager()) {
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    m_window = new Window(GAME_TITLE, GAME_WIN_W, GAME_WIN_H, 3, 3);
    m_input = new Input(m_window);
    m_input->init();

    const ShaderAttrib shaderVertexAttrib {
        .location = 0,
        .name = SHADER_POSITION_ATTRIB_NAME
    };

    const ShaderAttrib shaderTexCoordAttrib {
        .location = 1,
        .name = SHADER_TEXCOORD_ATTRIB_NAME
    };

    m_worldShader = new Shader(
        readFile(WORLD_VERTEX_SHADER_FILENAME),
        readFile(WORLD_FRAGMENT_SHADER_FILENAME),
        shaderVertexAttrib,
        shaderTexCoordAttrib);
    m_guiShader = new Shader(
        readFile(GUI_VERTEX_SHADER_FILENAME),
        readFile(GUI_FRAGMENT_SHADER_FILENAME),
        shaderVertexAttrib,
        shaderTexCoordAttrib);

    const std::initializer_list<TexParameter> textureParameters {
        TexParameter {GL_TEXTURE_MIN_FILTER, GL_NEAREST},
        TexParameter {GL_TEXTURE_MAG_FILTER, GL_NEAREST},
        TexParameter {GL_TEXTURE_WRAP_S, GL_REPEAT},
        TexParameter {GL_TEXTURE_WRAP_T, GL_REPEAT}
    };

    m_world = new World(
        glm::radians(GAME_CAMERA_FOV),
        F32(GAME_WIN_W) / F32(GAME_WIN_H),
        GAME_CAMERA_NEAR,
        GAME_CAMERA_FAR);
    m_world->setShader(m_worldShader);

    m_gui = new GUI(m_guiShader, m_input, m_window);

    m_player = new PlayerController(m_world, m_input);

    m_landscape = m_world->instantiate(World::defaultLayer);
    auto* landscapeEnt = m_landscape->getEntity();
    landscapeEnt->setLocalPosition(-unit_y * 3.0F);
    landscapeEnt->setLocalScale(glm::vec3 {5.0F});
    landscapeEnt->setMesh(m_assetManager->loadMesh(LANDSCAPE_MESH_FILEPATH));
    landscapeEnt->setTexture(m_assetManager->loadTexture(CLIFFS_TEXTURE_FILEPATH, textureParameters));
    m_landscape->setCollisionShapes(m_assetManager->loadCollision(LANDSCAPE_COLLISIONMESH_FILEPATH));

    const auto* pistol = m_world->instantiate(PISTOL_LAYER);
    auto* pistolEnt = pistol->getEntity();
    pistolEnt->setParent(m_world->getCamera()->getEntity());
    pistolEnt->setLocalPosition(glm::vec3 {1.5F, -2.5F, -5});
    pistolEnt->setLocalOrientation(glm::quat(glm::vec3 {0, glm::radians(-90.0F), 0}));
    pistolEnt->setMesh(m_assetManager->loadMesh(PISTOL_MESH_FILEPATH));
    pistolEnt->setTexture(m_assetManager->loadTexture(PISTOL_TEXTURE_FILEPATH, textureParameters));

    while (m_window->running()) {
        GLfloat deltaTime;
        m_window->beginFrame(deltaTime);
        m_input->begin();

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(CLEAR_COLOR);

        update(deltaTime);

        m_world->update(deltaTime);
        m_world->render();
        m_input->end();
        m_window->endFrame();
    }
}

GameEntryPoint::~GameEntryPoint() {
    delete m_player;
    delete m_input;
    delete m_gui;
    delete m_world;
    delete m_assetManager;
    delete m_window;
}

void GameEntryPoint::update(const GLfloat deltaTime) const {
    m_player->update(deltaTime);
}
