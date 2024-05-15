#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"

class Player : public GameObject {
public:
    explicit Player(Size size);

    void accelerateUp();
    void accelerateDown();
    void accelerateLeft();
    void accelerateRight();
};

#endif
