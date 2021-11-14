
#include "chpch.hpp"

#include <sstream>
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

	int score = 0;

	sf::Font font;
	font.loadFromFile("../assets/fonts/KOMIKAP_.ttf");

	sf::Text messageText;
	sf::Text scoreText;
	messageText.setFont(font);
	scoreText.setFont(font);
	messageText.setString("Press Enter to start");
	scoreText.setString("Score = 0");
	messageText.setCharacterSize(75);
	scoreText.setCharacterSize(100);
	messageText.setFillColor(sf::Color::Red);
	scoreText.setFillColor(sf::Color::Red);

	// position the text
	sf::FloatRect textRect = messageText.getLocalBounds();
	// set origin to the center of the text
	messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
	scoreText.setPosition(20, 20);

	window.draw(messageText);
	window.draw(scoreText);
	window.display();

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

		window.clear();

		if (!paused)
		{
			for (auto sprite : g_spriteLayers)
			{
				sprite->update(dt.asSeconds());
				std::stringstream ss;
				ss << "Score = " << score;
				scoreText.setString(ss.str());
			}
		}

		dt = clock.restart();
		

		
		for (const auto sprite : g_spriteLayers)
		{
			window.draw(sprite->getSprite());
			window.draw(scoreText);
			if (paused)
			{
				window.draw(messageText);
			}
		}
		window.display();
	}

	return 0;
}