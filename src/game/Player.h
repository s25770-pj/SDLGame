#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "IceBlock.h"
#include <SDL.h>

class Player : public GameObject {
private:
    int b_Size;

public:
    Player(float x, float y, int size);

    void setSize(int size);
    [[nodiscard]] int getSize() const;
    void draw(SDL_Renderer* renderer) override;
    bool checkCollision(const IceBlock& block);
};

#endif
