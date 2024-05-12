#include "GameObject.h"

GameObject::GameObject(float x, float y) : m_PositionX(x), m_PositionY(y), m_VelocityY(0.0f), m_Gravity(0.0f) {}

void GameObject::setPosition(float x, float y) {
    m_PositionX = x;
    m_PositionY = y;
}

float GameObject::getPositionX() const {
    return m_PositionX;
}

float GameObject::getPositionY() const {
    return m_PositionY;
}

void GameObject::setPositionY(float positionY) {
    m_PositionY = positionY;
}

void GameObject::setVelocityY(float VelocityY) {
    m_VelocityY = VelocityY;
}

void GameObject::move(float offsetX, float offsetY) {
    m_PositionX += offsetX;
    m_PositionY += offsetY;
}

void GameObject::draw(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect rect = { static_cast<int>(m_PositionX), static_cast<int>(m_PositionY)};
    SDL_RenderFillRect(renderer, &rect);
}

void GameObject::setGravity(float gravity) {
    m_Gravity = gravity;
}