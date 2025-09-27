#ifndef ENTITYS_H
#define ENTITYS_H

#include "raylib.h"
#include "raymath.h"

class Entity {
    private:
    public:
    virtual void update() = 0;
    virtual void debugRender() = 0;
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

    bool is_static = false;

    public:
    PhysicsEntity();
    PhysicsEntity(Vector2 pos, Vector2 size, float mass = 1, float damp = 1, bool is_static = false);

    virtual void debugRender() = 0;
    virtual void update() = 0;

    void setSize(Vector2 pos);
    Vector2 getSize();

    void setPos(Vector2 pos);
    Vector2 getPos();

    void setVel(Vector2 vel);
    Vector2 getVel();

    void applyForce(Vector2 force);
    void setForce(Vector2 force);
    Vector2 getForce();

    float getMass();
    void setMass(float mass);

    float getDamp();
    void setDamp(float damp);

    bool isStatic();
};

#endif