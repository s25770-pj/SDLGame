#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "../engine/PhysicsEngine.h"
#include <SDL.h>

class GameObject {
private:
    float m_PositionX;
    float m_PositionY;
    float m_VelocityY;
    float m_Gravity;
    PhysicsEngine physics;

public:
    GameObject(float x, float y);

    void setPosition(float x, float y);
    void setPositionY(float positionY);
    void setVelocityY(float VelocityY);
    [[nodiscard]] float getPositionX() const;
    [[nodiscard]] float getPositionY() const;
    void move(float offsetX, float offsetY);
    void update(float deltaTime);
    virtual void draw(SDL_Renderer* renderer);

    void setGravity(float gravity);
};

#endif
