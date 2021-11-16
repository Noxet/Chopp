
#include "chpch.hpp"

#include <sstream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

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
	}

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

	// hide it initially
	cp::SSprite rip("../assets/gfx/rip.png", 600, 2000);
	g_spriteLayers.push_back(&rip);

	// set up player, starting on the left side
	sf::Texture playerTexture;
	playerTexture.loadFromFile("../assets/gfx/player.png");
	sf::Sprite playerSprite;
	playerSprite.setTexture(playerTexture);
	playerSprite.setPosition(580, 720);
	side playerSide = side::LEFT;

	// set up axe
	sf::Texture axeTexture;
	axeTexture.loadFromFile("../assets/gfx/axe.png");
	sf::Sprite axeSprite;
	axeSprite.setTexture(axeTexture);
	axeSprite.setPosition(700, 830);
	constexpr float AXE_POS_LEFT = 700;
	constexpr float AXE_POS_RIGHT = 1075;

	// set up the flying log
	sf::Texture logTexture;
	logTexture.loadFromFile("../assets/gfx/log.png");
	sf::Sprite logSprite;
	logSprite.setTexture(logTexture);
	logSprite.setPosition(810, 720);
	bool logActive = false;
	float logSpeedX = 1000;
	float logSpeedY = -300;

	sf::Clock clock;
	sf::Time dt{};
	srand((int)time(0));

	bool paused = true;

	bool acceptInput{ false };

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
	scoreText.setFillColor(sf::Color::White);

	// background for score text
	const float scoreTextX = scoreText.getLocalBounds().getSize().x;
	const float scoreTextY = scoreText.getLocalBounds().getSize().y;
	// make the background a bit wider than the text
	sf::RectangleShape scoreRect(sf::Vector2f(scoreTextX + 40, scoreTextY + 20));
	scoreRect.setFillColor(sf::Color(0, 0, 0, 96));
	// start to the far left in x. Center the background in y (subtract 10 since we have 20px more height)
	scoreRect.setPosition(0, 20 + scoreText.getLocalBounds().top - 10);

	// position the text
	sf::FloatRect textRect = messageText.getLocalBounds();
	// set origin to the center of the text
	messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
	scoreText.setPosition(20, 20);

	// setup FPS counter
	sf::Text fpsText;
	fpsText.setFont(font);
	fpsText.setString("FPS = 0000");
	fpsText.setCharacterSize(100);
	fpsText.setFillColor(sf::Color::White);
	// make sure that al 3 decimals fit, and end at 1900, like score text starts at 20px
	fpsText.setPosition(1900 - fpsText.getLocalBounds().width, 20);
	// create background for text, by getting the implicit rectangle from the text
	const float fpsTextX = fpsText.getLocalBounds().getSize().x;
	const float fpsTextY = fpsText.getLocalBounds().getSize().y;
	sf::RectangleShape fpsRect(sf::Vector2f(fpsTextX + 40, fpsTextY + 20));
	fpsRect.setFillColor(sf::Color(0, 0, 0, 96));
	fpsRect.setPosition(1900 - fpsText.getLocalBounds().width - 20, 20 + fpsText.getLocalBounds().top - 10);

	// load branch texture
	sf::Texture branchTexture;
	branchTexture.loadFromFile("../assets/gfx/branch.png");

	// initialize branches and hide
	for (int i = 0; i < NUM_BRANCHES; ++i)
	{
		branches[i].setTexture(branchTexture);
		branches[i].setPosition(-2000, -2000);
		// set the origin to center
		branches[i].setOrigin(220, 20);
	}

	// setup sound
	
	// chopping sound
	sf::SoundBuffer chopBuffer;
	chopBuffer.loadFromFile("../assets/sfx/chop.wav");
	sf::Sound chop;
	chop.setBuffer(chopBuffer);

	// death sound
	sf::SoundBuffer deathBuffer;
	deathBuffer.loadFromFile("../assets/sfx/death.wav");
	sf::Sound death;
	death.setBuffer(deathBuffer);

	// out of time sound
	sf::SoundBuffer ootBuffer;
	ootBuffer.loadFromFile("../assets/sfx/out_of_time.wav");
	sf::Sound oot;
	oot.setBuffer(ootBuffer);

	// only update FPS counter each second
	float fpsCount{ 0 };

	while (window.isOpen())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}

		// start the game
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			paused = false;

			score = 0;

			// reset branches
			for (auto& branch : branchPositions)
			{
				branch = side::NONE;
			}

			// hide RIP
			rip.setX(675);
			rip.setY(2000);

			playerSprite.setPosition(580, 720);

			acceptInput = true;
		}

		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyReleased && !paused)
			{
				acceptInput = true;

				// hide the axe
				axeSprite.setPosition(2000, axeSprite.getPosition().y);
			}
		}

		if (acceptInput)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				playerSide = side::RIGHT;
				playerSprite.setPosition(1200, 720);

				score++;

				timeBar.addTime(2.0f / score + 0.15f);

				updateBranches();

				axeSprite.setPosition(AXE_POS_RIGHT, axeSprite.getPosition().y);

				// set the log flying to the right
				logSprite.setPosition(810, 720);
				logSpeedX = -1000;
				logActive = true;

				chop.play();

				acceptInput = false;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				playerSide = side::LEFT;
				playerSprite.setPosition(580, 720);

				score++;

				timeBar.addTime(2.0f / score + 0.15f);

				updateBranches();

				axeSprite.setPosition(AXE_POS_LEFT, axeSprite.getPosition().y);

				// set the log flying to the left
				logSprite.setPosition(810, 720);
				logSpeedX = 1000;
				logActive = true;

				chop.play();

				acceptInput = false;
			}
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
				// update the background to cover the text
				scoreRect.setSize(sf::Vector2f(scoreText.getLocalBounds().width + 40, scoreRect.getSize().y));

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

				// animate flying logs
				if (logActive)
				{
					float newLogX = logSprite.getPosition().x + logSpeedX * dt.asSeconds();
					float newLogY = logSprite.getPosition().y + logSpeedY * dt.asSeconds();
					logSprite.setPosition(newLogX, newLogY);

					if (newLogX < -100 || newLogX > 2000)
					{
						// stop animation and reset log position
						logActive = false;
						logSprite.setPosition(810, 720);
					}
				}

				// handling death. If the last log is on the player's side, we got hit.
				if (branchPositions[5] == playerSide)
				{
					paused = true;
					acceptInput = false;

					// draw RIP
					rip.setX(525);
					rip.setY(760);

					// hide player
					playerSprite.setPosition(2000, 660);
					axeSprite.setPosition(2000, 600);

					// set death text and center it
					messageText.setString("SQUASHED!!!");
					textRect = messageText.getLocalBounds();
					messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
					messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

					timeBar.reset();

					death.play();
				}

				if (timeBar.isGameOver())
				{
					paused = true;
					// Set new text an reposition to center
					messageText.setString("Out of time!!");
					textRect = messageText.getLocalBounds();
					messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
					messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

					timeBar.reset();

					oot.play();
				}
			}
		}

		fpsCount += dt.asSeconds();

		if (fpsCount >= 1)
		{
			std::stringstream ss;
			ss << "FPS = " << static_cast<int>(1.0f / dt.asSeconds());
			fpsText.setString(ss.str());
			fpsCount = 0;
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

		window.draw(playerSprite);
		window.draw(axeSprite);
		window.draw(logSprite);

		// draw score text
		window.draw(scoreRect);
		window.draw(scoreText);

		// draw FPS counter
		window.draw(fpsRect);
		window.draw(fpsText);

		if (paused)
		{
			window.draw(messageText);
		}

		window.display();
	}

	return 0;
}