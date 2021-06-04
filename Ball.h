#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Ball
{
private:
	Vector2f position;

	//A RectangleShape object called ref
	RectangleShape ballShape;

	float xVelocity = .2f;
	float yVelocity = .2f;

public:
	Ball(float startX, float startY);

	FloatRect getPosition();

	RectangleShape getShape();

	float getXVelocity();

	void reboundSides(); //What happens when ball hits the side of the screen?

	void reboundBatOrTop(); //What happens when ball hits the bat or top of the screen?

	void hitBottom(); //What happens when hits the bottom of the screen?

	void update();
};