
#include "chpch.hpp"

#include <SFML/Graphics.hpp>

int main()
{
	sf::VideoMode vm(1920, 1080);

	sf::RenderWindow window(vm, "Chopp!", sf::Style::Fullscreen);

	return 0;
}