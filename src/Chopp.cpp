
#include "chpch.hpp"

#include <sstream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Sprites/SSprite.hpp"
#include "Sprites/Actor.hpp"
#include "Sprites/Bee.hpp"
#include "Sprites/Cloud.hpp"
#include "Sprites/TimeBar.hpp"

// Store a reference to all layers
std::vector<cp::SSprite *> g_spriteLayers {};

constexpr int NUM_BRANCHES = 6;
sf::Sprite branches[NUM_BRANCHES];

// Where is the player/branch?
enum class side { LEFT, RIGHT, NONE };
side branchPositions[NUM_BRANCHES];

void updateBranches()
{
	for (int i = NUM_BRANCHES - 1; i > 0; --i)
	{
		branchPositions[i] = branchPositions[i - 1];

		// we want more empty spaces than branches
		int r = rand() % 5;
		switch (r)
		{
		case 0:
			branchPositions[0] = side::LEFT;
			break;

		case 1:
			branchPositions[0] = side::RIGHT;
			break;

		default:
			branchPositions[0] = side::NONE;
			break;
		}
	}
}

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

	cp::TimeBar timeBar;
	g_spriteLayers.push_back(&timeBar);

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

	sf::Texture branchTexture;
	branchTexture.loadFromFile("../assets/gfx/branch.png");

	for (int i = 0; i < NUM_BRANCHES; ++i)
	{
		branches[i].setTexture(branchTexture);
		branches[i].setPosition(-2000, -2000);
		// set the origin to center
		branches[i].setOrigin(220, 20);
	}

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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			updateBranches();
		}

		window.clear();

		/*
		 * The update code
		 */
		if (!paused)
		{
			for (auto sprite : g_spriteLayers)
			{
				sprite->update(dt.asSeconds());

				std::stringstream ss;
				ss << "Score = " << score;
				scoreText.setString(ss.str());

				// update the branches
				for (int i = 0; i < NUM_BRANCHES; ++i)
				{
					float height = i * 150;

					if (branchPositions[i] == side::LEFT)
					{
						// move the sprite to the left side
						branches[i].setPosition(610, height);
						// rotate it correctly
						branches[i].setRotation(180);
					}
					else if (branchPositions[i] == side::RIGHT)
					{
						branches[i].setPosition(1330, height);
						branches[i].setRotation(0);
					}
					else
					{
						// hide it
						branches[i].setPosition(3000, height);
					}
				}

				if (timeBar.isGameOver())
				{
					paused = true;
					// Set new text an reposition to center
					messageText.setString("Out of time!!");
					textRect = messageText.getLocalBounds();
					messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
					messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
				}
			}
		}

		dt = clock.restart();

		/*
		 * The render code
		 */
		for (const auto sprite : g_spriteLayers)
		{
			window.draw(sprite->getSprite());
			
		}

		// draw the branches
		for (const auto& branch : branches)
		{
			window.draw(branch);
		}

		// draw score text
		window.draw(scoreText);

		if (paused)
		{
			window.draw(messageText);
		}

		window.display();
	}

	return 0;
}