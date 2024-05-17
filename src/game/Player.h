#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"

class Player : public GameObject {
private:
    int health = 10;

public:
    explicit Player(Size size);

    void accelerateUp();
    void accelerateDown();
    void accelerateLeft();
    void accelerateRight();

    void setHealth(int damage);

    [[nodiscard]] int getHealth() const { return health; }
};

#endif
