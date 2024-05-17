#ifndef TIRE_OBJECT_H
#define TIRE_OBJECT_H

#include "GameObject.h"

class CarObject : public GameObject {
public:
    explicit CarObject(Size size) : GameObject(size, 0.0f, 0.0f, 0.0f, 2.0f) {}
};

#endif
