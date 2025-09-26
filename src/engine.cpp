#include "engine.h"

Engine::Engine() {
    InitWindow(500, 500, "Terraria Clone");

    physics_engine = PhysicsEngine();
    physics_thread = new std::thread(&Engine::thread_func, this); 
}

void Engine::run() {
    {
        std::lock_guard<std::mutex> lock(physics_running_mtx);

        physics_running = true;
    }

    Logger().log_info("Engine: Main loop started");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        EndDrawing();
    }

    Logger().log_info("Engine: Main loop finished");

    CloseWindow();

    {
        std::lock_guard<std::mutex> lock(closed_mtx);

        closed = true;
    }
}

void Engine::thread_func() {
    // wait for physics to start
    Logger().log_info("Engine: Waiting for Physics to start");
    while (true) {
        {
            std::lock_guard<std::mutex> lock(physics_running_mtx);

            if (physics_running) {
                break;
            }
        }

        {
            std::lock_guard<std::mutex> lock(closed_mtx);

            if (closed) {
                return;
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    Logger().log_info("Engine: Physics Started");

    // actual physics loop
    float frame_time = 0;
    float desired_time = 50; // 20 tps
    float catchup_time = 0;

    while (true) {
        auto start_time = std::chrono::system_clock::now();
        {
            std::lock_guard<std::mutex> lock(physics_engine_mtx);

            physics_engine.step();
        }
        auto end_time = std::chrono::system_clock::now();
        frame_time = std::chrono::duration<float, std::milli>(end_time - start_time).count();

        if (frame_time < desired_time) {
            catchup_time -= desired_time - frame_time;
            catchup_time = std::max(catchup_time, 0.0f);

            std::this_thread::sleep_for(std::chrono::milliseconds((int)(desired_time - frame_time)));
        }

        else if (frame_time > desired_time) {
            catchup_time += frame_time - desired_time;

            Logger().log_warning("Engine: Physics thread behind: " + std::to_string(catchup_time));
        }
    }

    Logger().log_info("Engine: Physics stopped");
}
