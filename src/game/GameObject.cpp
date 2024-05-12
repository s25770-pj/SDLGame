#include "GameObject.h"
// tylko do wizualizacji czy sie odbrze tworza na poprawnych kordynatrach, potem do wywalenia.

#include <iostream>

GameObject::GameObject(float x, float y) : m_PositionX(x), m_PositionY(y) {}

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

void GameObject::move(float offsetX, float offsetY) {
    m_PositionX += offsetX;
    m_PositionY += offsetY;
}

void GameObject::update() {
}

void GameObject::draw(SDL_Renderer* renderer) {
    // debug - do wywalenia potem
    std::cout << "Rysowanie obiektu na pozycji (" << m_PositionX << ", " << m_PositionY << ")" << std::endl;
}
