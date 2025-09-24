#include "engine.h"

Engine::Engine() {
    InitWindow(500, 500, "Terraria Clone");

    physics_engine = PhysicsEngine();
    physics_thread = new std::thread(&Engine::thread_func, this); 
}

void Engine::run() {
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        EndDrawing();
    }

    CloseWindow();
}

void Engine::thread_func() {
    // wait for physics to start
    while (true) {
        {
            std::lock_guard<std::mutex> lock(physics_running_mtx);

            if (physics_running) {
                break;
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    // actual physics loop
    float frame_time = 0;
    float desired_time = 50; // 20 tps

    while (true) {
        auto start_time = std::chrono::system_clock::now();
        {
            std::lock_guard<std::mutex> lock(physics_engine_mtx);

            physics_engine.step();
        }


    }
}
