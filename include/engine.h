#ifndef ENGINE_H
#define ENGINE_H

#include "raylib.h"
#include <thread>
#include <mutex>
#include <chrono>

#include "physics.h"

class Engine {
    private:
    PhysicsEngine physics_engine;
    std::mutex physics_engine_mtx;

    std::thread *physics_thread;

    bool physics_running = false;
    std::mutex physics_running_mtx;

    void thread_func();

    public:
    Engine();

    void run();
};

#endif