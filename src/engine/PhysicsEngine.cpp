#include "PhysicsEngine.h"

void PhysicsEngine::update(float &position, float &velocity, float acceleration, float gravity, float deltaTime) {
    // obliczanie prędkości
    velocity += (acceleration + gravity) * deltaTime;
    position += velocity * deltaTime;
}