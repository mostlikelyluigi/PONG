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

















//#include <SFML/Graphics.hpp>
//#include <string>
//
//
//int main(int argc, char const *argv[])
//{
//	int score = 0; //user starting score
//	float directionX, directionY, speed = 5; //
//
//	directionX = 0;
//	directionY = 0;
//
//	sf::RenderWindow window(sf::VideoMode(300, 400), "PONG GAME"); //Initialise window
//	
//	//Set a frame rate limit for the window...
//	window.setFramerateLimit(30); //...which is 60
//
//	//Set a nice font to show the score, lives and fps.
//	sf::Font font; /*Giving the class Font, the name "font".Font class included with SFML
//				   library*/
//
//	//Load the customised font
//	font.loadFromFile("MainFont.ttf");
//
//	//This is the text to be shown on screen: FPS, Score, Lives etc...
//	sf::Text text("", font);
//	text.setString(std::to_string(score)); //Set texts to string
//	text.setCharacterSize(30); //Character size
//	//text.setStyle(sf::Text::Bold); //Character Style
//	text.setFillColor(sf::Color::Black); //Character Color
//
//	//Creating the ball
//	sf::RectangleShape ball(sf::Vector2f(10, 10)); //Vector2f is defining size? 10,10
//	ball.setFillColor(sf::Color::Black); //Setting color of the ball to black
//	ball.setPosition(100, 100);//Ball Starting position
//
//	//Creating the bat the player plays with
//	sf::RectangleShape playerBat(sf::Vector2f(40, 10)); //Bat bigger on X-axis to make it longer than ball
//	playerBat.setFillColor(sf::Color::White); //Setting bat color to white
//	playerBat.setPosition(130, 385); //Setting starting position of the bat
//
//
//
//	//This loop runs forever lol, this also defines what happens while game window is open
//	while (window.isOpen())
//	{
//		//Get the position of the objects below: Ball and Player
//		sf::Vector2f ballPosition = ball.getPosition();
//		sf::Vector2f playerPosition = playerBat.getPosition();
//
//		//This is to detect collisions
//		if (ballPosition.x < 0)  //If on x axis ball changes position...
//			directionX = speed;  //Make direction of it equal to the speed. Speed = 5
//
//		else if (ballPosition.x > 300 - 10)
//			directionX = -speed;
//
//		if (ballPosition.y < 0)  //If on y axis ball changes position...
//			directionY = speed;	 //Make direction of it equal to the speed. Speed = 5
//		//Makes sure ball stays within the window.
//		else if (ballPosition.y > 400 - 10)
//		{
//			directionY = 0;
//
//			directionX = 0;
//		}
//
//
//		if (ballPosition.x >= playerPosition.x && ballPosition.x <= playerPosition.x + 40)
//			if (ballPosition.y >= playerPosition.y - 10)
//			{
//				score++;
//				text.setString(std::to_string(score)); //Set the text to the string "score"
//
//				directionY = -speed;
//			}
//			ball.move(directionX, directionY);//Move the ball
//
//			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
//			{
//				directionX = speed;
//				directionY = speed;
//				score = 0;
//			}
//
//			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
//			{
//				if (playerPosition.x > 0)
//					playerBat.move(-speed, 0);
//			}
//
//			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
//			{
//				if (playerPosition.x < 300 - 40)
//					playerBat.move(speed, 0);
//			}
//
//			//Check if the event window is closed
//			sf::Event event;
//			while (window.pollEvent(event))
//			{
//				if (event.type == sf::Event::Closed)
//					window.close();
//			}
//
//		//ALL this block of code below is for rendering purposes
//		//Clear the window to delete previous frame
//		window.clear();
//		//Then re-draw everything in the screen. Loop will repeat this.
//		//If It was ended with window.Clear() then nothing would appear on screen.
//		window.draw(ball);
//		window.draw(playerBat);
//		window.draw(text);
//		window.display();
//	}
//
//	return 0;
//}