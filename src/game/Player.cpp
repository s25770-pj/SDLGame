#include <iostream>
#include "Player.h"

Player::Player(Size size) : GameObject(size, 0.0f, 0.0f, 0.0f, 0.0f) {}

void Player::accelerateUp() {
    if (getSpeedY() > -4) {
        setSpeedY(getSpeedY()-0.1f);
    }
}

void Player::accelerateDown() {
    if (getSpeedY() < 4) {
        setSpeedY(getSpeedY()+0.1f);
    }
}

void Player::accelerateLeft() {
    if (getSpeedX() > -4) {
        setSpeedX(getSpeedX()-0.1f);
    }
}

void Player::accelerateRight() {
    if (getSpeedX() < 4) {
        setSpeedX(getSpeedX()+0.1f);
    }
}

void Player::setHealth(int damage) {
    health -= damage;
}

