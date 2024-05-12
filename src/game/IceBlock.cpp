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

void IceBlock::draw() {
    //debug - do wywalenia potem
    std::cout << "Rysowanie bloku lodu o rozmiarze " << b_Size << " na pozycji (" << getPositionX() << ", " << getPositionY() << ")" << std::endl;
}
