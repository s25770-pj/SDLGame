#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "IceBlock.h"
#include <SDL.h>

class Player : public GameObject {
private:
    int b_Size;
    bool m_IsJumping;
    bool m_IsOnIceBlock;
    float m_JumpVelocity;
    PhysicsEngine physics;

public:
    Player(float x, float y, int size);

    void setSize(int size);
    [[nodiscard]] int getSize() const;
    [[nodiscard]] int getHeight() const;
    void draw(SDL_Renderer* renderer) override;
    bool checkCollision(const IceBlock& block);
    void jump();
    void setIsOnIceBlock(bool isOnIceBlock) { m_IsOnIceBlock = isOnIceBlock; }
    [[nodiscard]] bool getIsOnIceBlock() const { return m_IsOnIceBlock; }
};

#endif
