#include "GameObject.h"
#include <iostream>

using namespace std;

GameObject::GameObject(Size size, float accelerationX, float accelerationY, float speedX, float speedY) : objectSize(size), accelerationX(accelerationX), accelerationY(accelerationY), speedX(speedX), speedY(speedY), texture(nullptr) {}

void GameObject::setSpeedX(float speed) {
    speedX = speed;
}

void GameObject::setSpeedY(float speed) {
    speedY = speed;
}

void GameObject::setTexture(SDL_Texture* tex) {
    texture = tex;
}

void GameObject::move() {
    objectSize.positionX += (int)speedX+(int)accelerationX;
    objectSize.positionY += (int)speedY+(int)accelerationY;
}

void GameObject::draw(SDL_Renderer* renderer) const {
    if (texture) {
        SDL_Rect rect = { objectSize.positionX, objectSize.positionY, objectSize.width, objectSize.height };
        SDL_RenderCopy(renderer, texture, nullptr, &rect);
    } else {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_Rect rect = { objectSize.positionX, objectSize.positionY, objectSize.width, objectSize.height };
        SDL_RenderFillRect(renderer, &rect);
    }
}

void GameObject::draw(SDL_Renderer* renderer, int r, int g, int b) const {
    if (texture) {
        draw(renderer);
    } else {
        SDL_SetRenderDrawColor(renderer, r, g, b, 255);
        SDL_Rect rect = { objectSize.positionX, objectSize.positionY, objectSize.width, objectSize.height };
        SDL_RenderFillRect(renderer, &rect);
    }
}

bool GameObject::checkCollision(const GameObject& other) const {
    SDL_Rect thisRect = {getPositionX(), getPositionY(), getW(), getH()};
    SDL_Rect otherRect = {other.getPositionX(), other.getPositionY(), other.getW(), other.getH()};
    SDL_Rect intersection;

    return SDL_IntersectRect(&thisRect, &otherRect, &intersection) == SDL_TRUE;
}
