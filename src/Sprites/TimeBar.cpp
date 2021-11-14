#include "chpch.hpp"

#include "TimeBar.hpp"


namespace cp
{
	TimeBar::TimeBar() : SSprite("")
	{
		m_timebar.setSize(sf::Vector2f(m_startWidth, m_height));
		m_timebar.setFillColor(sf::Color::Red);
		m_timebar.setPosition((1920 / 2.0f) - m_startWidth / 2.0f, 980);
	}


	void TimeBar::update(float dt)
	{
		SSprite::update(dt);

		// reduce time, and adjust the width accordingly
		m_timeRemaining -= dt;
		// cap it to 0
		if (m_timeRemaining <= 0) m_timeRemaining = 0;
		m_timebar.setSize(sf::Vector2f(m_widthPerSecond * m_timeRemaining, m_height));
	}


	const sf::Drawable& TimeBar::getSprite() const
	{
		return m_timebar;
	}
}
