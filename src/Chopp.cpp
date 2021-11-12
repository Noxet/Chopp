
#include "chpch.hpp"

#include <SFML/Graphics.hpp>

int main()
{
	sf::VideoMode vm(1920, 1080);
	sf::RenderWindow window(vm, "Chopp!", sf::Style::Default);

	// A texture to hold a graphic on the GPU
	sf::Texture bgTexture;
	bgTexture.loadFromFile("../assets/gfx/background.png");

	// Create a sprite, load the texture, and set it to cover the screen
	sf::Sprite bgSprite;
	bgSprite.setTexture(bgTexture);
	bgSprite.setPosition(0, 0);

	while (window.isOpen())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}

		window.clear();
		window.draw(bgSprite);
		window.display();
	}

	return 0;
}