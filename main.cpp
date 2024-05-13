#include <iostream>
#include "Window.h"

void update(double deltaTime) {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
}

int main() {
    const auto window = new Window("Test", 800, 600, update, 3, 3);

    window->run();
    delete window;
}
