#include "chpch.hpp"

#include "Cloud.hpp"

namespace cp
{
	Cloud::Cloud(const std::string& imgPath) : Actor(imgPath)
	{
		reset();
	}


	Cloud::Cloud(const std::string& imgPath, const float xPos, const float yPos) : Actor(imgPath, xPos, yPos)
	{
		reset();
	}


	void Cloud::update(float dt)
	{
		Actor::update(dt);

		if (!m_isActive) return;

		m_xPos += m_xSpeed * dt;
		// stop if outside the screen completely
		if (m_xPos > 1920)
		{
			m_isActive = false;
			reset();
		}

		m_sprite.setPosition(m_xPos, m_yPos);
	}


	void Cloud::reset()
	{
		Actor::reset();

		m_xPos = -300; // start outside screen
		m_yPos = rand() % 150;
		m_xSpeed = rand() % 200;
		m_isActive = true;
		m_sprite.setPosition(m_xPos, m_yPos);
	}
}
