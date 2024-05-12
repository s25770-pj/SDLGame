#include "IceBlock.h"
// tylko do wizualizacji czy sie odbrze tworza na poprawnych kordynatrach, potem do wywalenia.
#include <iostream>

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

    // Rysowanie platformy
    SDL_RenderFillRect(renderer, &rect);

    std::cout << "Rysowanie bloku lodu o rozmiarze " << b_Size << " na pozycji (" << getPositionX() << ", " << getPositionY() << ")" << std::endl;
}
