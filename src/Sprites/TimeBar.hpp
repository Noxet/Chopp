#pragma once

#include "SSprite.hpp"

namespace cp
{
	class TimeBar : public SSprite
	{
	public:
		TimeBar();

		virtual void update(float dt) override;
		virtual const sf::Drawable& getSprite() const override;

		bool isGameOver() const { return m_timeRemaining <= 0; }

		void addTime(float time);
		void reset();

	private:
		sf::RectangleShape m_timeBar;
		float m_startWidth{ 400 };
		float m_height{ 80 };
		float m_timeRemaining{ 6.0f };
		float m_widthPerSecond{ m_startWidth / m_timeRemaining };
	};
}