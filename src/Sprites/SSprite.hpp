#pragma once

#include <SFML/Graphics.hpp>


namespace cp
{
	/**
	 * A static sprite class
	 */
	class SSprite
	{
	public:
		SSprite(std::string imgPath);
		SSprite(std::string imgPath, float xPos, float yPos);

		virtual void update(float dt);

		sf::Sprite getSprite() const { return m_sprite; }

		void setX(float xPos) { m_xPos = xPos; }
		void setY(float yPos) { m_yPos = yPos; }
		float getX() { return m_xPos; }
		float getY() { return m_yPos; }

	protected:
		// A texture to hold a graphic on the GPU
		sf::Texture m_texture;
		// Create a sprite, load the texture, and set it to cover the screen
		sf::Sprite m_sprite;

		// Co-ordinates for where to draw the sprite in the window
		float m_xPos{};
		float m_yPos{};
	};
}
