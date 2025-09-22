#ifndef ENTITYS_H
#define ENTITYS_H

#include "raylib.h"

class Entity {
    private:
    public:
    Entity();
};

class PhysicsEntity : public Entity {
    private:
    Vector2 pos;
    Vector2 vel = {0, 0};

    Vector2 force = {0, 0};

    float mass;
    float damp;

    public:
    PhysicsEntity(Vector2 pos, float mass = 1, float damp = 1);

    void debugRender();
};

#endif