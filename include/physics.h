#ifndef PHYSICS_H
#define PHYSICS_H

#include <vector>
#include "raylib.h"
#include "raymath.h"

#include "entities.h"
#include "tilemap.h"

class PhysicsEngine {
    private:
    std::vector<PhysicsEntity*> enities;
    int entity_count = 0;
    
    float gravity = 0.0f;

    Tilemap *tilemap;

    public:
    PhysicsEngine();

    void addEntity(PhysicsEntity *entity);
    void addTilemap(Tilemap *tilemap);

    void debugRender();

    void step();
};

#endif