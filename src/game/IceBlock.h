#ifndef ICE_BLOCK_H

#include "GameObject.h"

class IceBlock : public GameObject {
private:
    int b_Size;

public:
    IceBlock(float x, float y, int size);
    void setSize(int size);
    [[nodiscard]] int getSize() const;
    void draw() override;
};

#endif
