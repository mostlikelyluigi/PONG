#include "Ball.h"

//This is the constructor and it is called when the object is created
Ball::Ball(float startX, float startY)
{
	position.x = startX;
	position.y = startY;

	ballShape.setSize(sf::Vector2f(10, 10));
	ballShape.setPosition(position);
}

FloatRect Ball::getPosition()
{
	return ballShape.getGlobalBounds();
}

RectangleShape Ball::getShape()
{
	return ballShape; //Returns copy of RectangleShape to be drawn on screen
}

float Ball::getXVelocity()
{
	return xVelocity;//Return stored value of xVelocity
}

void Ball::reboundSides()
{
	xVelocity = -xVelocity; //When side of screen is hit, change velocity to opposite direction
}

void Ball::reboundBatOrTop()
{
	position.y -= (yVelocity * 30); //This prevents the ball getting stuck in the Bat! :D
	yVelocity = -yVelocity; //Just change velocity to opposite direction
}

void Ball::hitBottom()
{
	//Position the ball to the top-middle of the screen
	position.y = 1; 
	position.x = 500;
}

void Ball::update()
{
	// Update the ball position variables
	position.y += yVelocity;
	position.x += xVelocity;

	// Move the ball and the bat
	ballShape.setPosition(position);
}