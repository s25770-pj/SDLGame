#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SDL.h>

struct Size {
    int positionX = 0;
    int positionY = 0;
    int width = 20;
    int height = 25;
};

class GameObject {
private:
    Size objectSize;
    float accelerationX=0.0f;
    float accelerationY=0.0f;
    float speedX=0.0f;
    float speedY=0.0f;

public:
    explicit GameObject(Size Size, float accelerationX, float accelerationY, float speedX, float speedY);

    void setSpeedX(float speed);
    void setSpeedY(float speed);

    [[nodiscard]] int getW() const { return objectSize.width; }
    [[nodiscard]] int getH() const { return objectSize.height; }
    [[nodiscard]] int getPositionX() const { return objectSize.positionX; }
    [[nodiscard]] int getPositionY() const { return objectSize.positionY; }
    [[nodiscard]] float getSpeedX() const { return speedX; }
    [[nodiscard]] float getSpeedY() const { return speedY; }

    [[nodiscard]] SDL_Rect getSDLRect() const { return {getPositionX(), getPositionY(), getW(), getH() };}

    void move();

    void draw(SDL_Renderer* renderer) const;
    void draw(SDL_Renderer* renderer, int r, int g, int b) const;

    bool checkCollision(GameObject) const;
};

#endif
