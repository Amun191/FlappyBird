#include <SFML/Graphics.hpp>
#include <iostream>

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

GameState state = GameState::Start;


int main()
{
//Texts
	sf::Font font("04B_30__.TTF");
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
	tex.loadFromFile("Bird.png");
	tex.setSmooth(false);
	sf::Sprite bird(tex);
	bird.setPosition(sf::Vector2f(20,400));

	sf::Texture pipe;
	pipe.loadFromFile("tube.png");
	pipe.setSmooth(false);
	sf::Sprite tube1(pipe);
	sf::Sprite tube2(pipe);
	sf::Sprite tube3(pipe);


	double velocity = 0;
	double gravity = 0.4;
	double jumpVelo = 5;
	double PosX = 0;
	double PosY = 400;
	double tube1PosX = 500;
	double tube1PosY = 0;
	double tube2PosX = 850;
	double tube2PosY = 0;
	double tube3PosX = 1200;
	double tube3PosY = 0;
	int tubeSpeed = 2;
	sf::Angle currentRotation ;
	sf::Angle targetRotation;
	sf::Color background(255,255,255,255);
	// sf::Angle angleDown = sf::degrees(305);
	// sf::Angle angleUp = sf::degrees(470);

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

			velocity += gravity;
			if(velocity > MAXVELOCITY){
				velocity = MAXVELOCITY;
			}
			PosY += velocity;
			tube1PosX -= tubeSpeed;
			tube2PosX -= tubeSpeed;
			tube3PosX -= tubeSpeed;
			targetRotation = sf::degrees(velocity * 4);
			if(targetRotation < sf::degrees(-30)) targetRotation = sf::degrees(-30);
			if(targetRotation > sf::degrees(90)) targetRotation = sf::degrees(90);

			currentRotation += (targetRotation - currentRotation) * 0.1;

			// tube1.getPosition;




			bird.setPosition(sf::Vector2f(20,PosY));
			bird.setRotation(currentRotation);
			tube1.setPosition(sf::Vector2f(tube1PosX, tube1PosY));
			tube2.setPosition(sf::Vector2f(tube2PosX,tube2PosY));
			tube3.setPosition(sf::Vector2f(tube3PosX,tube3PosY));

			double posTube1x = tube1.getPosition().x;
			double posTube2x = tube2.getPosition().x;
			double posTube3x = tube3.getPosition().x;
			if(posTube1x < -200){tube1PosX += 700;}
			if(posTube2x < -200){tube2PosX += 700;}
			if(posTube3x < -200) {tube3PosX += 700;} 
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