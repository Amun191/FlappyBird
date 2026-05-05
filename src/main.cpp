#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

const double MAXVELOCITY = 10;
// class Bird{
// public:
// 	std::string name;
// 	sf::Texture texture;
// 	sf::Sprite sprite;

// 	Bird(std::string name, sf::Texture tex, sf::Sprite spr)
// 	: name(name), tex(texture), spr(sprite) {}; 
// };
enum class GameState{
	Start,
	Playing,
	Menu,
	settings,
	deathscreen
};

void setPos(sf::Sprite& tube){
	float x = tube.getPosition().x;
	float y = tube.getPosition().y;
	x = 500;
	y = 50 + std::rand() % 100;

	tube.setPosition({x,y});
}

GameState state = GameState::Start;


int main()
{
//Texts
	std::cout << "PROGRAM STARTED\n" << std::flush;
	std::srand(std::time(nullptr));
	sf::Font font("assets/04B_30__.TTF");
	sf::Color fontcolor(173,247,240, 255);
	sf::Text gamename(font);
	gamename.setString("FlappyBird");
	gamename.setCharacterSize(50);
	gamename.setFillColor(fontcolor);
	gamename.setStyle(sf::Text::Bold);
	gamename.setPosition(sf::Vector2f(50,100));
	sf::Text pressEnter(font);
	pressEnter.setString("Press Enter to start...");
	pressEnter.setCharacterSize(20);
	pressEnter.setFillColor(fontcolor);
	pressEnter.setPosition(sf::Vector2f(68,150));

	sf::RenderWindow window( sf::VideoMode( {500,800}), "FlappyBird" );
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);

//Sprites
	sf::Texture tex;
	tex.loadFromFile("assets/Bird.png");
	tex.setSmooth(false);
	sf::Sprite bird(tex);
	bird.setPosition(sf::Vector2f(20,400));

	sf::Texture pipe;
	pipe.loadFromFile("assets/tube.png");
	pipe.setSmooth(false);
	sf::Sprite tube1(pipe);
	sf::Sprite tube2(pipe);
	sf::Sprite tube3(pipe);

	sf::Texture back;
	back.loadFromFile("assets/background.png");
	back.setSmooth(false);
	sf::Sprite backgroundGame(back);


	float velocity = 0;
	float gravity = 0.4;
	float jumpVelo = 5;
	int backGroundPosX = 0;
	int backGroundPosY = 0;
	float tubeSpeed = 2;
	sf::Angle currentRotation ;
	sf::Angle targetRotation;
	sf::Color background(255,255,255,255);
	// sf::Angle angleDown = sf::degrees(305);
	// sf::Angle angleUp = sf::degrees(470);
	bird.setPosition(sf::Vector2f(20,400));
	tube1.setPosition({500,0});
	tube2.setPosition({850,0});
	tube3.setPosition({1200,0});

	while ( window.isOpen() )
	{
		while ( const std::optional event = window.pollEvent() )
		{
			if ( event->is<sf::Event::Closed>() )
				window.close();
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)){
				//bird here
				velocity -= jumpVelo;
				if(velocity > MAXVELOCITY){
					velocity = MAXVELOCITY;
				}
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)){
				state = GameState::Playing;
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)){
				if(state == GameState::Menu){
					state = GameState::Playing;
				}else{
					state = GameState::Menu;
				}
				
			}
		}

		window.clear(background);
		if (state == GameState::Start)
		{
			window.draw(gamename);
			window.draw(pressEnter);
		}

		if (state == GameState::Playing)
		{
			window.draw(backgroundGame);
			backgroundGame.setPosition(sf::Vector2f(backGroundPosX, backGroundPosY));
			backGroundPosX -= 1;
			if (backGroundPosX == -500) backGroundPosX = 0;

			velocity += gravity;
			if(velocity > MAXVELOCITY){
				velocity = MAXVELOCITY;
			}
			bird.move({0,+velocity});

			tube1.move({-tubeSpeed, 0});
			tube2.move({-tubeSpeed, 0});
			tube3.move({-tubeSpeed,0});

			targetRotation = sf::degrees(velocity * 4);
			if(targetRotation < sf::degrees(-30)) targetRotation = sf::degrees(-30);
			if(targetRotation > sf::degrees(90)) targetRotation = sf::degrees(90);
			currentRotation += (targetRotation - currentRotation) * 0.1;
			bird.setRotation(currentRotation);

			
			if(tube1.getPosition().x < -500){
				setPos(tube1);
			}
			if(tube2.getPosition().x < -500){
				setPos(tube2);
			}
			if(tube3.getPosition().x< -500) {
				setPos(tube3);
			} 
			std::cout << tube1.getPosition().x << std::endl;
			window.draw(bird);
			window.draw(tube1);
			window.draw(tube2); 
			window.draw(tube3);

		}


		if(state == GameState::Menu)
		{
			//.... menu stuff
		}

		if(state == GameState::settings)
		{
			//....
		}


		

		window.display();
	}
}