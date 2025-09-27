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
    
    float gravity = 0.0f;

    public:
    PhysicsEngine();

    void addEntity(PhysicsEntity *entity);
    void debugRender();

    void step();
};

#endif