#include "chpch.hpp"

#include "Bee.hpp"

namespace cp
{
	void Bee::update()
	{
		SSprite::update();

		std::cout << "Bee::update called" << std::endl;

		m_xPos += 0.1f;
		m_sprite.setPosition(m_xPos, m_yPos);
	}
}
