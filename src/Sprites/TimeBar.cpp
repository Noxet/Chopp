#include "chpch.hpp"

#include "TimeBar.hpp"


namespace cp
{
	TimeBar::TimeBar() : SSprite("")
	{
		m_timeBar.setSize(sf::Vector2f(m_startWidth, m_height));
		m_timeBar.setFillColor(sf::Color::Red);
		m_timeBar.setPosition((1920 / 2.0f) - m_startWidth / 2.0f, 980);
	}


	void TimeBar::update(float dt)
	{
		SSprite::update(dt);

		// reduce time, and adjust the width accordingly
		m_timeRemaining -= dt;
		// cap it to 0
		if (m_timeRemaining <= 0) m_timeRemaining = 0;
		m_timeBar.setSize(sf::Vector2f(m_widthPerSecond * m_timeRemaining, m_height));
	}


	const sf::Drawable& TimeBar::getSprite() const
	{
		return m_timeBar;
	}


	void TimeBar::addTime(float time)
	{
		m_timeRemaining += time;
		if (m_timeRemaining >= 6.0f) m_timeRemaining = 6.0f;
	}


	void TimeBar::reset()
	{
		m_timeRemaining = 6.0f;
	}
}
