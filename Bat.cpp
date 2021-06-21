#include "Bat.h"

//Setting size and starting position of the bat
Bat::Bat(float startX, float startY)
{
    position.x = startX;
    position.y = startY;

    batShape.setSize(sf::Vector2f(5, 100));
    batShape.setPosition(position);
}

//This is to get the coordinates of the bat
FloatRect Bat::getPosition()
{
    return batShape.getGlobalBounds();
}

//Making the bat, and getShape() just calls back the "bat"
RectangleShape Bat::getShape()
{
    return batShape;
}

//Handle the bat movement
void Bat::moveUp()
{
    position.y -= batSpeed;
}
void Bat::moveDown()
{
    position.y += batSpeed;
}
void Bat::update()
{
    batShape.setPosition(position);
}