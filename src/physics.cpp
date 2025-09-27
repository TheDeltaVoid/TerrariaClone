#include "physics.h"

PhysicsEngine::PhysicsEngine() {

}

void PhysicsEngine::addTilemap(Tilemap *tilemap) {
    this->tilemap = tilemap;
}

void PhysicsEngine::addEntity(PhysicsEntity *entity) {
    enities.push_back(entity);
    entity_count++;
}

void PhysicsEngine::debugRender() {
    for (int i = 0; i < entity_count; i++) {
        enities.at(i)->debugRender();
    }

    tilemap->debugRender();
}

void PhysicsEngine::step() {
    for (int i = 0; i < entity_count; i++) {
        PhysicsEntity *e = enities.at(i);

        if (e->isStatic()) {
            continue;
        }

        Vector2 a = Vector2Scale(e->getForce(), 1.0f / e->getMass());
        e->setVel(e->getVel() + a);

        e->setForce({0, 0});

        e->setVel(Vector2Scale(e->getVel(), e->getDamp()));

        //std::vector<TileCollider*> colliders = tilemap->getEntitiesRange({e->getPos().x, e->getPos().y, e->getSize().x, e->getSize().y});
        std::vector<TileCollider*> colliders = tilemap->getEntities();

        // collision x axis
        Vector2 new_pos = Vector2Add(e->getPos(), {e->getVel().x, 0});
        for (int i = 0; i < colliders.size(); i++) {
            TileCollider *other = colliders.at(i);

            if (CheckCollisionRecs({new_pos.x, new_pos.y, e->getSize().x, e->getSize().y}, {other->getPos().x, other->getPos().y, other->getSize().x, other->getSize().y})) {
                if (e->getVel().x > 0) {
                    new_pos.x = other->getPos().x - e->getSize().x;
                } else if (e->getVel().x < 0) {
                    new_pos.x = other->getPos().x + other->getSize().x;
                }
                
                e->setVel({0, e->getVel().y});
            }
        }

        e->setPos(new_pos);


        // collision y axis
        new_pos = Vector2Add(e->getPos(), {0, e->getVel().y});
        for (int i = 0; i < colliders.size(); i++) {
            TileCollider *other = colliders.at(i);

            if (CheckCollisionRecs({new_pos.x, new_pos.y, e->getSize().x, e->getSize().y}, {other->getPos().x, other->getPos().y, other->getSize().x, other->getSize().y})) {
                if (e->getVel().y > 0) {
                    new_pos.y = other->getPos().y - e->getSize().y;
                } else if (e->getVel().y < 0) {
                    new_pos.y = other->getPos().y + other->getSize().y;
                }
                
                e->setVel({e->getVel().x, 0});
            }
        }

        e->setPos(new_pos);
    }
}
