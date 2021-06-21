#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Bat
{
private:
    Vector2f position;
    //rectangleshape object
    RectangleShape batShape;
    float batSpeed = .3f;
public:
    Bat(float startX, float startY);
    FloatRect getPosition();
    RectangleShape getShape();
    void moveUp();
    void moveDown();
    void update();
};