#include "PhysicsEngine.h"

PhysicsEngine PhysicsEngine::update(const double dt) const {
    PhysicsEngine updated = *this;
    updated.p = p + v * dt + a*dt*dt/2.0;
    updated.v = v + a * dt;
    updated.a = a;
    return updated;
}
