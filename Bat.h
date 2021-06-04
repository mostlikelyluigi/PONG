#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Bat
{
private:
	Vector2f position;

	// A Rectangle Shape object
	RectangleShape batShape;

	float batSpeed = .3f;

public:
	Bat(float startX, float startY); //function Bat

	FloatRect getPosition(); //returns FloatRect, the 4 points which define a rectangle

	RectangleShape getShape(); //this just returns a rectangle shape :D
	

	void moveLeft();

	void moveRight();

	void update();
};