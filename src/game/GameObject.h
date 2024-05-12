#ifndef GAME_OBJECT_H

class GameObject {
private:
    float m_PositionX;
    float m_PositionY;

public:
    GameObject(float x, float y);

    void setPosition(float x, float y);
    void move(float offsetX, float offsetY);
    void update();
    void draw();
};

#endif
