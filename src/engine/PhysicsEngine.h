#ifndef PHYSICS_ENGINE_H
#define PHYSICS_ENGINE_H

class PhysicsEngine {
public:
    void update(float &position, float &velocity, float acceleration, float gravity, float deltaTime);
    void jump(float &velocity, float jumpVelocity);
};

#endif