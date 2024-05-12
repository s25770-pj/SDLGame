#include "PhysicsEngine.h"

void PhysicsEngine::update(float &position, float &velocity, float acceleration, float deltaTime) {
    // Obliczanie prędkości i położenia na podstawie przyśpieszenia
    velocity += acceleration * deltaTime;
    position += velocity * deltaTime;
}