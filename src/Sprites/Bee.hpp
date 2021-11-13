#pragma once

#include "Actor.hpp"

namespace cp
{
	class Bee : public cp::Actor
	{
	public:
		Bee(const std::string& imgPath);
		Bee(const std::string& imgPath, const float xPos, const float yPos);

		virtual void update(float dt) override;

	private:
		virtual void reset() override;
	};
}
