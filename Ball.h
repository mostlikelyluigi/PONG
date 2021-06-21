#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Ball
{
private:
    Vector2f position;
    RectangleShape ballShape;

    float xVelocity = .2f;
    float yVelocity = .2f;

public:
    Ball(float startX, float startY);
    FloatRect getPosition();
    RectangleShape getShape();
    float getYVelocity();
    void reboundSideLeft();
    void reboundSideRight();
    void reboundTopOrBottom();
    void reboundBat();

    void update();

};