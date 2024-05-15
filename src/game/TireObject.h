#ifndef TIRE_OBJECT_H
#define TIRE_OBJECT_H

#include "GameObject.h"

class TireObject : public GameObject {
public:
    explicit TireObject(Size size) : GameObject(size, 0.0f, 0.0f, 0.0f, 0.0f) {}
};

#endif
