#include <functional>
#include <iostream>
#include <utility>
#include "Window.h"
#include "Shader.h"

void update(double deltaTime) {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

int main() {
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    const auto window = new Window("Test", 800, 600, update, 3, 3);

    const VAO vertexArray;
    vertexArray.bind();

    VBO vertexBuffer;
    GLfloat vertices[8] = {
        0.5F, 0.5F,
        0.5F, -0.5F,
        -0.5F, -0.5F,
        -0.5F, 0.5F
    };
    vertexBuffer.store(vertices, 8);
    glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, nullptr);

    EBO elementBuffer;
    GLuint indices[6] = {
        0, 1, 3,
        1, 2, 3
    };
    elementBuffer.store(indices, 6);

    const std::string vertexShader =
    "#version 150 \n"
    "in vec3 in_position;"
    "void main(void) {"
    "    gl_Position = vec4(in_position, 1.0);"
    "}";

    const std::string fragmentShader =
    "#version 150 \n"
    "out vec4 out_color;"
    "void main(void) {"
    "    out_color = vec4(1, 0, 0, 1);"
    "}";

    const Shader shader (vertexShader, fragmentShader, ShaderAttrib {0, "in_position"});
    shader.use();
    glEnableVertexAttribArray(0);

    window->run();
    delete window;
}
