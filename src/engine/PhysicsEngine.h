#ifndef PHYSICS_ENGINE_H
#define PHYSICS_ENGINE_H
#include <array>

using position_t = std::array<double, 2>;

position_t operator+(const position_t &a, const position_t &b) {
    return {a[0]+b[0],a[1]+b[1]};
}
position_t operator-(const position_t &a, const position_t &b) {
    return {a[0]-b[0],a[1]-b[1]};
}
position_t operator*(const position_t &a, const double &b) {
    return {a[0]*b,a[1]*b};
}
position_t operator/(const position_t &a, const double &b) {
    return {a[0]/b,a[1]/b};
}

class PhysicsEngine {
private:
    position_t p;
    position_t v;
    position_t a;

public:
    [[nodiscard]] PhysicsEngine update(double) const;
};

#endif