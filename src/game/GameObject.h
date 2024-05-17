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
    float accelerationX;
    float accelerationY;
    float speedX;
    float speedY;
    SDL_Texture* texture;

public:
    explicit GameObject(Size Size, float accelerationX, float accelerationY, float speedX, float speedY);

    void setSpeedX(float speed);
    void setSpeedY(float speed);
    void setTexture(SDL_Texture* tex);

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

    [[nodiscard]] bool checkCollision(const GameObject& other) const;
};

#endif
