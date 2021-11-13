#include "chpch.hpp"
#include "Bee.hpp"

namespace cp
{
	Bee::Bee(const std::string& imgPath) : Actor(imgPath)
	{
		reset();
	}


	Bee::Bee(const std::string& imgPath, const float xPos, const float yPos) : Actor(imgPath, xPos, yPos)
	{
		reset();
	}

	void Bee::update(float dt)
	{
		Actor::update(dt);

		if (!m_isActive) return;

		m_xPos -= m_xSpeed * dt;
		// stop if outside the screen completely
		if (m_xPos < -100)
		{
			m_isActive = false;
			reset();
		}
		
		m_sprite.setPosition(m_xPos, m_yPos);
	}


	void Bee::reset()
	{
		Actor::reset();

		// reset state of bee
		m_xPos = 2000;
		m_yPos = (rand() % 1350) + 500;
		m_isActive = true;
	}
}
