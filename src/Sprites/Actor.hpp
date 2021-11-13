#pragma once

#include "SSprite.hpp"

namespace cp
{
	class Actor : public SSprite
	{
	public:
		Actor(const std::string& imgPath);
		Actor(const std::string& imgPath, const float xPos, const float yPos);

		virtual void update(float dt) override;
		void setActive(const bool active) { m_isActive = active; }

		void setSpeed(const float speed) { m_xSpeed = speed; }

	protected:
		bool m_isActive{ false };
		float m_xSpeed{};

		// reset state
		virtual void reset();
	};
}
