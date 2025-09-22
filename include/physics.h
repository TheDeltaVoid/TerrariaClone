#ifndef PHYSICS_H
#define PHYSICS_H

#include <vector>
#include "entitys.h"

class PhysicsEngine {
    private:
    std::vector<PhysicsEntity*> enities;
    int entity_count = 0;
    float tps = 60;

    public:
    PhysicsEngine();

    void addEntity(PhysicsEntity *entity);
    void debugRender();

    void step();
};

#endif