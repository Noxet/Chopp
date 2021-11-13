
#include "chpch.hpp"

#include <vector>
#include <SFML/Graphics.hpp>

#include "Sprites/SSprite.hpp"
#include "Sprites/Actor.hpp"
#include "Sprites/Bee.hpp"
#include "Sprites/Cloud.hpp"

// Store a reference to all layers
std::vector<cp::SSprite *> g_spriteLayers {};

int main()
{
	sf::VideoMode vm(1920, 1080);
	sf::RenderWindow window(vm, "Chopp!", sf::Style::Fullscreen);

	cp::SSprite bg("../assets/gfx/background.png", 0, 0);
	g_spriteLayers.push_back(&bg);

	cp::Cloud cloud1("../assets/gfx/cloud.png", 0, 0);
	cloud1.setActive(true);
	g_spriteLayers.push_back(&cloud1);
	cp::Cloud cloud2("../assets/gfx/cloud.png", 0, 250);
	cloud2.setActive(true);
	g_spriteLayers.push_back(&cloud2);
	cp::Cloud cloud3("../assets/gfx/cloud.png", 0, 500);
	cloud3.setActive(true);
	g_spriteLayers.push_back(&cloud3);
	bool cloud1Active{ false };
	bool cloud2Active{ false };
	bool cloud3Active{ false };
	float cloud1Speed{ 0.0f };
	float cloud2Speed{ 0.0f };
	float cloud3Speed{ 0.0f };

	cp::SSprite tree("../assets/gfx/tree.png", 810, 0);
	g_spriteLayers.push_back(&tree);

	cp::Bee bee("../assets/gfx/bee.png", 500, 500);
	bee.setActive(true);
	bee.setSpeed((rand() % 200) + 200);
	g_spriteLayers.push_back(&bee);

	sf::Clock clock;
	sf::Time dt{};
	srand((int)time(0));

	bool paused = true;

	while (window.isOpen())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			paused = false;
		}

		// don't process any data is paused, just wait for input
		if (paused) continue;

		window.clear();

		for (auto sprite : g_spriteLayers)
		{
			sprite->update(dt.asSeconds());
			std::cout << "FPS: " << 1.0f / dt.asSeconds() << std::endl;
		}

		dt = clock.restart();
		

		
		for (const auto sprite : g_spriteLayers)
		{
			window.draw(sprite->getSprite());
		}
		window.display();
	}

	return 0;
}