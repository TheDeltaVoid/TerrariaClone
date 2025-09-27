#ifndef ENGINE_H
#define ENGINE_H

#include "raylib.h"
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>

#include "physics.h"
#include "logger.h"
#include "game.h"
#include "tilemap.h"

class Engine {
    private:
    PhysicsEngine physics_engine;
    std::mutex physics_engine_mtx;

    std::thread *physics_thread;

    bool physics_running = false;
    std::mutex physics_running_mtx;

    bool closed = false;
    std::mutex closed_mtx;

    std::vector<PhysicsEntity*> entities;
    std::mutex entities_mtx;

    Tilemap tilemap;
    std::mutex tilemap_mtx;

    float tps = 240;

    void thread_func();

    public:
    Engine();

    void run();
};

#endif