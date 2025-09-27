#include "game.h"

Player::Player() {
    setSize(Vector2({1, 1}));
    setPos(Vector2({0, 0}));

    setMass(10.0f);
    setDamp(0.80f);
}

void Player::update() {
    if (IsKeyDown(KEY_UP)) {
        applyForce(Vector2({0, -10}));
    }

    if (IsKeyDown(KEY_LEFT)) {
        applyForce(Vector2({-10, 0}));
    }

    if (IsKeyDown(KEY_DOWN)) {
        applyForce(Vector2({0, 10}));
    }

    if (IsKeyDown(KEY_RIGHT)) {
        applyForce(Vector2({10, 0}));
    }
}

void Player::debugRender() {
    DrawRectangleV(getPos(), getSize(), RED);
}
