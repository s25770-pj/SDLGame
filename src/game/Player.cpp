#include <iostream>
#include "Player.h"

Player::Player(float x, float y, int size) : GameObject(x, y), b_Size(size) {}

void Player::setSize(int size) {
    b_Size = size;
}

int Player::getSize() const {
    return b_Size;
}

int Player::getHeight() const {
    return b_Size+5;
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

void Player::jump() {
    if (!m_IsJumping) {
        m_IsJumping = true;
        setVelocityY(-m_JumpVelocity);
    }
}

void GameObject::update(float deltaTime) {
    physics.update(m_PositionY, m_VelocityY, 0.0f, m_Gravity, deltaTime);
}

bool Player::checkCollision(const IceBlock& block) {
    SDL_Rect playerRect = {
            (int)getPositionX(),
            (int)getPositionY(),
            b_Size,
            b_Size + 5
    };

    SDL_Rect blockRect = {
            (int)block.getPositionX(),
            (int)block.getPositionY(),
            block.getSize(),
            block.getSize() + 5
    };

    std::cout << blockRect.x << "|" << blockRect.y << "|" << blockRect.w << "|" << blockRect.h << std::endl;
    std::cout << playerRect.x << "|" << playerRect.y << "|" << playerRect.w << "|" << playerRect.h << std::endl;

    if (playerRect.x + playerRect.w > blockRect.x &&
        playerRect.x < blockRect.x + blockRect.w &&
        playerRect.y + playerRect.h >= blockRect.y - 5 &&
        playerRect.y + playerRect.h <= blockRect.y + 5) {
        return true;
    } else {
        return false;
    }
}
