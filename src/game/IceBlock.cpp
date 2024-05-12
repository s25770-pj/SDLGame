#include "IceBlock.h"

IceBlock::IceBlock(float x, float y, int size) : GameObject(x, y), b_Size(size) {}

void IceBlock::setSize(int size) {
    b_Size = size;
}

int IceBlock::getSize() const {
    return b_Size;
}

void IceBlock::draw(SDL_Renderer* renderer) {
    //debug - do wywalenia potem
    SDL_SetRenderDrawColor(renderer, 113, 166, 210, 255);

    // pozycja i wymiary platformy
    SDL_Rect rect = {
            static_cast<int>(getPositionX()), //x lewego gornego rogu
            static_cast<int>(getPositionY()), //y lewego gornego rogu
            b_Size, //wielkosc
            20 //wysokosc
    };

    // rysowanie platformy
    SDL_RenderFillRect(renderer, &rect);
}
