#include "physics.h"

PhysicsEngine::PhysicsEngine() {

}

void PhysicsEngine::addEntity(PhysicsEntity *entity) {
    enities.push_back(entity);
    entity_count++;
}

void PhysicsEngine::debugRender() {
    for (int i = 0; i < entity_count; i++) {
        enities.at(i)->debugRender();
    }
}

void PhysicsEngine::step() {
    for (int i = 0; i < entity_count; i++) {
        PhysicsEntity *e = enities.at(i);

        Vector2 a = Vector2Scale(e->getForce(), 1.0f / e->getMass());
        e->setVel(e->getVel() + a);

        e->setForce({0, 0});

        e->setVel(Vector2Scale(e->getVel(), e->getDamp()));

        e->setPos(Vector2Add(e->getPos(), e->getVel()));
    }
}
