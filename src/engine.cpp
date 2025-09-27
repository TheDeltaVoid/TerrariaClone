#include "engine.h"

Engine::Engine() {
    // SetConfigFlags(FLAG_FULLSCREEN_MODE | FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT);
    // InitWindow(1920, 1080, "Terraria Clone");

    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT);
    InitWindow(600, 600, "Terraria Clone");

    physics_engine = PhysicsEngine();

    int index = (int)entities.size();
    Player *p = new Player();
    entities.push_back(p);

    physics_engine.addEntity(entities[index]);

    // SetTargetFPS(100);

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

        physics_engine.debugRender();

        DrawFPS(10, 10);
        EndDrawing();
    }

    Logger().log_info("Engine: Main loop finished");

    {
        std::lock_guard<std::mutex> lock(closed_mtx);

        closed = true;
    }

    CloseWindow();

    {
        std::lock_guard<std::mutex> lock(entities_mtx);

        for (int i = 0; i < entities.size(); i++) {
            delete entities[i];
        }

    }

    physics_thread->join();
    delete physics_thread;
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
    float desired_time = 1 / tps;
    float catchup_time = 0;

    while (true) {
        auto start_time = std::chrono::steady_clock::now();

        {
            std::lock_guard<std::mutex> lock(closed_mtx);

            if (closed) {
                break;
            }
        }

        {
            std::lock_guard<std::mutex> lock(entities_mtx);

            for (int i = 0; i < entities.size(); i++) {
                entities[i]->update();
            }
        }

        {
            std::lock_guard<std::mutex> lock(physics_engine_mtx);

            physics_engine.step();

            if (IsKeyDown(KEY_P)) {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
        }
        auto end_time = std::chrono::steady_clock::now();
        frame_time = std::chrono::duration<float>(end_time - start_time).count();

        // Logger().log_info("Engine: Physics frame time: " + std::to_string(frame_time) + "s" + ", " + std::to_string(desired_time) + "s");

        if (frame_time < desired_time) {
            // Logger().log_info("Engine: Physics thread sleeping: " + std::to_string((int)((desired_time - frame_time) * 1000)));

            float sleep_time = (desired_time - frame_time);

            if (catchup_time > 0) {
                if (catchup_time <= sleep_time) {
                    sleep_time -= catchup_time;
                    catchup_time = 0;
                }

                else {
                    catchup_time -= sleep_time;
                    sleep_time = 0;
                }
            }

            if (sleep_time > 0) {
                std::this_thread::sleep_for(std::chrono::milliseconds((int)(sleep_time * 1000)));
            }
        }

        else if (frame_time > desired_time) {
            catchup_time += frame_time - desired_time;
        }

        if (catchup_time > 0) {
            Logger().log_warning("Engine: Physics thread behind: " + std::to_string(catchup_time));
        }
    }

    Logger().log_info("Engine: Physics stopped");
}
