#include "chpch.hpp"

#include "SSprite.hpp"

namespace cp
{
	SSprite::SSprite(std::string imgPath)
	{
		m_texture.loadFromFile(imgPath);
		m_sprite.setTexture(m_texture);

		// Randomize positions
		m_xPos = (rand() % 500) + 500;
		m_yPos = (rand() % 500) + 500;
		m_sprite.setPosition(m_xPos, m_yPos);
	}


	SSprite::SSprite(std::string imgPath, float xPos, float yPos)
	{
		m_texture.loadFromFile(imgPath);
		m_sprite.setTexture(m_texture);

		m_xPos = xPos;
		m_yPos = yPos;
		m_sprite.setPosition(m_xPos, m_yPos);
	}


	void SSprite::update(float dt)
	{
	}


	void SSprite::setX(float xPos)
	{
		m_xPos = xPos;
		m_sprite.setPosition(m_xPos, m_yPos);
	}


	void SSprite::setY(float yPos)
	{
		m_yPos = yPos;
		m_sprite.setPosition(m_xPos, m_yPos);
	}
}
