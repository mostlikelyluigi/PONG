#include "bat.h"
#include "ball.h"
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


/*Side note: header files list the publicibly accessible instance variables and methods in the class
             definition; .cpp files are used to implement those methods.*/

using namespace sf;
using namespace std;

//Define the sfx path
#define HIT_SOUND_FILEPATH "Music/PongSound.wav"
#define BACKGROUND_THEME "Music/backgroundTheme.ogg"

int main()
{
    //Create a window of 1024x768 pixels in size
    int windowWidth = 1024;
    int windowHeight = 768;

    //Loading the soundbuffer for the sfx
    sf::SoundBuffer _hitSoundBuffer;
    sf::Sound _hitSound;

    //Load the sfx file
    if (!_hitSoundBuffer.loadFromFile( HIT_SOUND_FILEPATH ))
    {
        std::cout << "Error loading the sfx file" << std::endl;
    }

    _hitSound.setBuffer(_hitSoundBuffer);


    //PLAY BACKGROUND MUSIC
    sf::Music backgroundTheme;
    
   //open the music file
    if (!backgroundTheme.openFromFile(BACKGROUND_THEME))
    {
        std::cout << "Error importing the background theme file" << std::endl;
    }
    //Make sure the music loops
    backgroundTheme.setLoop(true);
    //Play the background theme
    backgroundTheme.play();


    //Make the title of the window "PONG"
    RenderWindow window(VideoMode(windowWidth, windowHeight), "PONG");
    window.setSize(Vector2u(windowWidth, windowHeight));


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

    //Handle ball hitting the bottom of the screen
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

            _hitSound.play(); //Play the sfx sound when the ball hits the bat
        }

        //Handle the bat hitting the left side of the screen (Screen collision)
        if (bat.getPosition().left < 0.f)
        {
            bat.reboundSideL();
        }
        
        //Handle the bat hitting the right side of the screen (Screen collision)
        if (bat.getPosition().left + 10 > windowWidth)
        {
            bat.reboundSideR();
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