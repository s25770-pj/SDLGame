#ifndef WALL_OBJECT_H
#define WALL_OBJECT_H

#include "GameObject.h"

class WallObject : public GameObject {
public:
    explicit WallObject(Size size) : GameObject(size, 0.0f, 0.0f, 0.0f, 0.0f) {}
};

#endif //WALL_OBJECT_H
