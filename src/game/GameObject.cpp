#include "GameObject.h"

GameObject::GameObject(Size size, float accelerationX, float accelerationY, float speedX, float speedY) : objectSize(size) {}

void GameObject::setPosition(int x, int y) {
    objectSize.positionX = x;
    objectSize.positionY = y;
}

void GameObject::setAccelerationX(float speed) {
    accelerationX = speed;
}

void GameObject::setAccelerationY(float speed) {
    accelerationY = speed;
}

void GameObject::setSpeedX(float speed) {
    speedX = speed;
}

void GameObject::setSpeedY(float speed) {
    speedY = speed;
}

void GameObject::move(int offsetX, int offsetY) {
    objectSize.positionX += offsetX+(int)accelerationX;
    objectSize.positionY += offsetY+(int)accelerationY;
}

void GameObject::draw(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect rect = { objectSize.positionX, objectSize.positionY, objectSize.width, objectSize.height };
    SDL_RenderFillRect(renderer, &rect);
}

bool GameObject::checkCollision(SDL_Rect rect1, SDL_Rect rect2) {
    return SDL_IntersectRect(&rect1, &rect2, nullptr);
}
