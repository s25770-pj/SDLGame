#include "Player.h"

Player::Player(float x, float y, int size) : GameObject(x, y), b_Size(size) {}

void Player::setSize(int size) {
    b_Size = size;
}

int Player::getSize() const {
    return b_Size;
}

void Player::draw(SDL_Renderer* renderer) {
    //debug - do wywalenia potem
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    // pozycja i wymiary gracza
    SDL_Rect rect = {
            static_cast<int>(getPositionX()), //x lewego gornego rogu
            static_cast<int>(getPositionY()), //y lewego gornego rogu
            b_Size, //wielkosc
            b_Size + 5 //wysokosc
    };

    // rysowanie platformy
    SDL_RenderFillRect(renderer, &rect);
}

void GameObject::update(float deltaTime) {
    physics.update(m_PositionY, m_VelocityY, 0.0f, m_Gravity, deltaTime);
}

bool Player::checkCollision(const IceBlock& block) {
    SDL_Rect playerRect = {
            static_cast<int>(getPositionX()),
            static_cast<int>(getPositionY()),
            b_Size,
            b_Size + 5
    };
    SDL_Rect blockRect = {
            static_cast<int>(block.getPositionX()),
            static_cast<int>(block.getPositionY()),
            block.getSize(),
            block.getSize() + 5
    };

    return SDL_HasIntersection(&playerRect, &blockRect) == SDL_TRUE;
}
