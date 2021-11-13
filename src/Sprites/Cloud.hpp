#pragma once

#include "Actor.hpp"

namespace cp
{
	class Cloud : public Actor
	{
	public:
		Cloud(const std::string& imgPath);
		Cloud(const std::string& imgPath, const float xPos, const float yPos);

		virtual void update(float dt) override;

	protected:
		virtual void reset() override;
	};
}
