#include "GameObject.h"
#include <iostream>

GameObject::GameObject(float x, float y) : m_PositionX(x), m_PositionY(y) {}

void GameObject::setPosition(float x, float y) {
    m_PositionX = x;
    m_PositionY = y;
}

void GameObject::move(float offsetX, float offsetY) {
    m_PositionX += offsetX;
    m_PositionY += offsetY;
}

void GameObject::update() {
}

void GameObject::draw() {
    std::cout << "Rysowanie obiektu na pozycji (" << m_PositionX << ", " << m_PositionY << ")" << std::endl;
}
