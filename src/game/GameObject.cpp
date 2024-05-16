#include "GameObject.h"
#include <iostream>

using namespace std;

GameObject::GameObject(Size size, float accelerationX, float accelerationY, float speedX, float speedY) : objectSize(size) {}

void GameObject::setSpeedX(float speed) {
    speedX = speed;
}

void GameObject::setSpeedY(float speed) {
    speedY = speed;
}

void GameObject::move() {
    objectSize.positionX += (int)speedX+(int)accelerationX;
    objectSize.positionY += (int)speedY+(int)accelerationY;
}

void GameObject::draw(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect rect = { objectSize.positionX, objectSize.positionY, objectSize.width, objectSize.height };
    SDL_RenderFillRect(renderer, &rect);
}

void GameObject::draw(SDL_Renderer* renderer, int r, int g, int b) const {
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_Rect rect = { objectSize.positionX, objectSize.positionY, objectSize.width, objectSize.height };
    SDL_RenderFillRect(renderer, &rect);
}

bool GameObject::checkCollision(GameObject rect) const {
    SDL_Rect player = {getPositionX(), getPositionY(), getW(), getH()};
    SDL_Rect c_rect = {rect.getPositionX(), rect.getPositionY(), rect.getW(), rect.getH()};

    return SDL_IntersectRect(&player, &c_rect, &c_rect) == SDL_TRUE;
}
