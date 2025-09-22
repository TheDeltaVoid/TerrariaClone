#include "physics.h"

PhysicsEngine::PhysicsEngine() {

}

void PhysicsEngine::addEntity(PhysicsEntity *entity) {
    enities.push_back(entity);
    entity_count++;
}

void PhysicsEngine::debugRender() {

}
