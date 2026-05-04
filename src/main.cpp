#include <SFML/Graphics.hpp>
#include <iostream>
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
	settings
};

GameState state = GameState::Start;


int main()
{
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


	sf::Texture tex;
	tex.loadFromFile("Bird.png");
	tex.setSmooth(false);
	sf::Sprite bird(tex);
	bird.setPosition(sf::Vector2f(0,400));
	double velocity = 0;
	double gravity = 0.4;
	double jumpVelo = 5;
	double PosX = 0;
	double PosY = 400;




	while ( window.isOpen() )
	{
		while ( const std::optional event = window.pollEvent() )
		{
			if ( event->is<sf::Event::Closed>() )
				window.close();
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)){
				//bird here
				velocity -= jumpVelo;
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)){
				state = GameState::Playing;
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)){
				if(state == GameState::Menu){
					state == GameState::Playing;
				}else{
					state = GameState::Menu;
				}
				
			}
	
		}

		window.clear();

		if (state == GameState::Start)
		{
			window.draw(gamename);
			window.draw(pressEnter);
		}

		if (state == GameState::Playing)
		{

			velocity += gravity;
			if(velocity > 10){
				velocity = 10;
			}
			PosY += velocity;
			bird.setPosition(sf::Vector2f(0,PosY));
			window.draw(bird);

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