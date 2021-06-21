#include <SFML/Graphics.hpp>
#include "Bat.h"
#include "Ball.h"
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <SFML/Audio.hpp>

using namespace sf;
using namespace std;

#define HIT_SOUND_FILEPATH "Music/PongSound.wav"
#define BACKGROUND_THEME "Music/backgroundTheme.ogg"


int main()
{

    int windowWidth = 1024;
    int windowHeight = 768;
    RenderWindow window(VideoMode(windowWidth, windowHeight), "PONG GAME");
    int score = 0;
    int lives = 3;

    //Loading the soundbuffer for the sfx
    sf::SoundBuffer _hitSoundBuffer;
    sf::Sound _hitSound;

    //Load the sfx file
    if (!_hitSoundBuffer.loadFromFile(HIT_SOUND_FILEPATH))
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

    //Make the 2 bats and set their relative position
    Bat bat(windowWidth - 20, windowHeight / 2);
    Bat bat2(20, windowHeight / 2);

    //Make the ball
    Ball ball(500, 250);


    //Handle the text and font
    Text hud;
    Font font;
    font.loadFromFile("MainFont.ttf");
    hud.setFont(font);
    hud.setCharacterSize(75);
    hud.setFillColor(sf::Color::White);

    while (window.isOpen())
    {
       
        //Check if the event window is closed
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

//=========================================================================================
 
        //Input handler
        if (Keyboard::isKeyPressed(Keyboard::Up))
        {
            bat.moveUp();
        }
        else if (Keyboard::isKeyPressed(Keyboard::Down))
        {
            bat.moveDown();
        }
        else if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::W))
        {
            bat2.moveUp();
        }
        else if (Keyboard::isKeyPressed(Keyboard::S))
        {
            bat2.moveDown();
        }

//=========================================================================================

        //Handle the ball hitting the top / bottom of the window
        if (ball.getPosition().top > windowHeight || ball.getPosition().top < windowHeight)
        {
            ball.reboundTopOrBottom();
        }

        //Handle the ball hitting the left side of the window
        if (ball.getPosition().left < 0)
        {
            ball.reboundSideLeft();

            //Remove a life
            lives--;

            //Check for zero lives
            if (lives < 1)
            {
                //Reset the score
                score = 0;
                //Reset the lives
                lives = 3;
            }
        }

        //Handle the ball hitting the right side of the window
        if (ball.getPosition().left + 10 > windowWidth)
        {
            ball.reboundSideRight();

            //Remove a life
            lives--;

            //Check for zero lives
            if (lives < 1)
            {
                //Reset the score
                score = 0;
                //Reset the lives
                lives = 3;
            }
        }

        //Handle the ball hitting the bat
        if (ball.getPosition().intersects(bat.getPosition()))
        {
            ball.reboundBat();
            score++;

            _hitSound.play(); //Play the sfx sound when the ball hits the bat
        }

        //Handle the ball hitting the second bat
        if (ball.getPosition().intersects(bat2.getPosition()))
        {
            ball.reboundBat();
            
            score++;

            _hitSound.play(); //Play the sfx sound when the ball hits the bat
        }

//=========================================================================================


        ball.update();
        bat.update();
        bat2.update();
        std::stringstream ss;
        ss << "Score: " << score << "   Lives: " << lives;
        hud.setString(ss.str());

//=========================================================================================

        //This is all for rendering purposes
        window.clear(Color(26, 128, 182, 255));
        window.draw(bat.getShape());
        window.draw(bat2.getShape());
        window.draw(ball.getShape());
        window.draw(hud);

        window.display();
    }
    
    return 0;
}

