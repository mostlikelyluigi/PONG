#include "bat.h"
#include "ball.h"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>


/*Side note: header files list the publicibly accessible instance variables and methods in the class
             definition; .cpp files are used to implement those methods.*/

using namespace sf;

int main()
{
    //Create a window of 1024x768 pixels in size
    int windowWidth = 1024;
    int windowHeight = 768;

    //Make the title of the window "PONG"
    RenderWindow window(VideoMode(windowWidth, windowHeight), "PONG");

    int score = 0;
    int lives = 3;

    //Create the bat
    Bat bat(windowWidth / 2, windowHeight - 20);

    //Create the ball
    Ball ball(windowWidth / 2, 1);

    //Create text object called "message"
    Text hud;

    //Font for the text above
    Font font;
    font.loadFromFile("ARCADECLASSIC.TTF");

    //Set font to the message
    hud.setFont(font);

    //Make is massive lol
    hud.setCharacterSize(75);

    //Just the color
    hud.setFillColor(sf::Color::White);

    //This loop goes round forever lol
    while (window.isOpen())
    {
        //Handle player input

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                //This means player closed the window
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            //move left
            bat.moveLeft();
        }
        else if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            //move right
            bat.moveRight();
        }
        else if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            //quit
            window.close();
        }

        //Frame update

    //Handle ball hitting hte bottom of the screen
        if (ball.getPosition().top > windowHeight)
        {
            //reverse the direction of the ball
            ball.hitBottom();

            //remove a life from the player
            lives--;

            //Check for zero lives
            if (lives < 1)
            {
                //reset the score
                score = 0;
                //reset the lives
                lives = 3;
            }
        }

        //Handle the ball hittin the top of the screen
        if (ball.getPosition().top < 0)
        {
            ball.reboundBatOrTop();

            //Add a point to the players score
            score++;
        }

        //Handle the ball hitting sides
        if (ball.getPosition().left < 0 || ball.getPosition().left + 10 > windowWidth)
        {
            ball.reboundSides();
        }

        //Has the ball hit the bat?
        if (ball.getPosition().intersects(bat.getPosition()))
        {
            //Hit detected so reverse the ball and score a point
            ball.reboundBatOrTop();
        }

        ball.update();
        bat.update();

        //Update the HUD text
        std::stringstream ss;
        ss << "Score:" << score << "     Lives:" << lives;
        hud.setString(ss.str());


        //Draw the frame

        //Clear everything from the last frame
        window.clear(Color(26, 128, 182, 255));

        window.draw(bat.getShape());
        window.draw(ball.getShape());

        //Draw the score
        window.draw(hud);

        //show everything
        window.display();
    }

    return 0;
}