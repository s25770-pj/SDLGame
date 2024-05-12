#ifndef GAME_OBJECT_H

#include <SDL.h>

class GameObject {
private:
    float m_PositionX;
    float m_PositionY;

public:
    GameObject(float x, float y);

    void setPosition(float x, float y);
    [[nodiscard]] float getPositionX() const;
    [[nodiscard]] float getPositionY() const;
    void move(float offsetX, float offsetY);
    void update();
    virtual void draw(SDL_Renderer* renderer);
};

#endif
