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
    m_input = new Input(m_window->getHandle());
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

    m_world = new World(
        glm::radians(GAME_CAMERA_FOV),
        F32(GAME_WIN_W) / F32(GAME_WIN_H),
        GAME_CAMERA_NEAR,
        GAME_CAMERA_FAR);
    m_world->setShader(m_worldShader);

    m_gui = new GUI(m_guiShader, m_input, m_window);

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
    delete m_input;
    delete m_gui;
    delete m_world;
    delete m_assetManager;
    delete m_window;
}

void GameEntryPoint::update(GLfloat &deltaTime) {
    //TODO: Game loop implementation
}