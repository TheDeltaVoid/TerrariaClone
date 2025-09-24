#ifndef PHYSICS_H
#define PHYSICS_H

#include <vector>
#include "raylib.h"
#include "raymath.h"

#include "entities.h"

class PhysicsEngine {
    private:
    std::vector<PhysicsEntity*> enities;
    int entity_count = 0;
    float tps = 60;
    
    float gravity = 9.8f;

    public:
    PhysicsEngine();

    void addEntity(PhysicsEntity *entity);
    void debugRender();

    void step();
};

#endif