#ifndef TRUCK_OBJECT_H
#define TRUCK_OBJECT_H

#include "GameObject.h"

class TruckObject : public GameObject {
public:
    explicit TruckObject(Size size) : GameObject(size, 0.0f, 0.0f, 0.0f, 0.0f) {}
};

#endif //TRUCK_OBJECT_H
