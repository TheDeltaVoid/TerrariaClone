#ifndef ENTITYS_H
#define ENTITYS_H

#include "raylib.h"
#include "raymath.h"

class Entity {
    private:
    public:
    Entity();
};

class PhysicsEntity : public Entity {
    private:
    Vector2 pos;
    Vector2 size;

    Vector2 vel = {0, 0};

    Vector2 force = {0, 0};

    float mass;
    float damp;

    public:
    PhysicsEntity(Vector2 pos, Vector2 size, float mass = 1, float damp = 1);

    void debugRender();

    void setPos(Vector2 pos);
    Vector2 getPos();

    void setVel(Vector2 vel);
    Vector2 getVel();

    void applyForce(Vector2 force);
    void setForce(Vector2 force);
    Vector2 getForce();

    float getMass();
    float getDamp();
};

#endif