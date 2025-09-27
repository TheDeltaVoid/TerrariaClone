#include "entities.h"

Entity::Entity () {}

PhysicsEntity::PhysicsEntity() {};

PhysicsEntity::PhysicsEntity(Vector2 pos, Vector2 size, float mass, float damp) {
    this->pos = pos;
    this->size = size;

    this->mass = mass;
    this->damp = damp;
}

void PhysicsEntity::setSize(Vector2 size) { this->size = size; };
Vector2 PhysicsEntity::getSize() { return size; };

void PhysicsEntity::setPos(Vector2 pos) { this->pos = pos; };
Vector2 PhysicsEntity::getPos() { return pos; };

void PhysicsEntity::setVel(Vector2 vel) { this->vel = vel; };
Vector2 PhysicsEntity::getVel() { return vel; };

void PhysicsEntity::applyForce(Vector2 force) { this->force = Vector2Add(this->force, force); };
void PhysicsEntity::setForce(Vector2 force) { this->force = force; };
Vector2 PhysicsEntity::getForce() { return force; };

float PhysicsEntity::getMass() { return mass; };
void PhysicsEntity::setMass(float mass) { this->mass = mass; };

float PhysicsEntity::getDamp() { return damp; };
void PhysicsEntity::setDamp(float damp) { this->damp = damp; };
