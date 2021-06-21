#include "Ball.h"

//Setting the size of the ball and its starting position
Ball::Ball(float startX, float startY)
{
    position.x = startX;
    position.y = startY;

    ballShape.setSize(sf::Vector2f(10, 10));
    ballShape.setPosition(position);
}

//Gets the coordinates of the ball
FloatRect Ball::getPosition()
{
    return ballShape.getGlobalBounds();
}
//This just returns the ball
RectangleShape Ball::getShape()
{
    return ballShape;
}
float Ball::getYVelocity()
{
    return yVelocity;
}

//Did the ball hit the top or bottom?
void Ball::reboundTopOrBottom()
{
    yVelocity = -yVelocity;
}

//Did the ball hit the left side?
void Ball::reboundSideLeft()
{
    position.y = 250;
    position.x = 500;

}
//Did the ball hit the right side?
void Ball::reboundSideRight()
{
    position.y = 250;
    position.x = 500;
}

//Did the ball hit the bat?
void Ball::reboundBat()
{
    position.x -= (xVelocity * 30);
    xVelocity = -xVelocity;

}

void Ball::update()
{
    position.y += yVelocity;
    position.x += xVelocity;

    ballShape.setPosition(position);
}
