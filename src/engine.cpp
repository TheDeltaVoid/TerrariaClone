#include "engine.h"

#include "raylib.h"

Engine::Engine() {
    InitWindow(500, 500, "Terraria Clone");
}

void Engine::run() {
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        EndDrawing();
    }

    CloseWindow();
}
