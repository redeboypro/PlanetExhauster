#include "Game/GameEntryPoint.h"

int main() {
    const auto* gameController = new GameEntryPoint();
    delete gameController;
}
