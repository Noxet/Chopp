#include "chpch.hpp"

#include "SSprite.hpp"

namespace cp
{
	SSprite::SSprite(std::string imgPath) : SSprite(imgPath, 0, 0)
	{

	}


	SSprite::SSprite(std::string imgPath, float xPos, float yPos)
	{
		m_texture.loadFromFile(imgPath);
		m_sprite.setTexture(m_texture);

		m_xPos = xPos;
		m_yPos = yPos;
		m_sprite.setPosition(m_xPos, m_yPos);
	}


	void SSprite::update()
	{
		std::cout << "SSPrite::update called" << std::endl;
	}
}
