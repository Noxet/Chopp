
#include "chpch.hpp"

#include <vector>
#include <SFML/Graphics.hpp>

#include "Sprites/SSprite.hpp"
#include "Sprites/Bee.hpp"

std::vector<cp::SSprite> g_spriteLayers {};

int main()
{
	sf::VideoMode vm(1920, 1080);
	sf::RenderWindow window(vm, "Chopp!", sf::Style::Default);

	cp::SSprite bg("../assets/gfx/background.png");
	g_spriteLayers.push_back(bg);
	cp::SSprite tree("../assets/gfx/tree.png", 810, 0);
	g_spriteLayers.push_back(tree);
	cp::Bee bee("../assets/gfx/bee.png", 0, 800);
	g_spriteLayers.push_back(bee);
	bool beeActive{ false };
	float beeSpeed{ 0.0f };


	while (window.isOpen())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}

		for (auto& sprite : g_spriteLayers)
		{
			sprite.update();
		}

		window.clear();
		for (const auto& sprite : g_spriteLayers)
		{
			window.draw(sprite.getSprite());
		}
		window.display();
	}

	return 0;
}