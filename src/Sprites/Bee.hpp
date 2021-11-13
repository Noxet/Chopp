#pragma once

#include "SSprite.hpp"

namespace cp
{
	class Bee : public SSprite
	{
	public:
		Bee(const std::string& imgPath) : SSprite(imgPath) {}
		Bee(const std::string& imgPath, const float xPos, const float yPos) : SSprite(imgPath, xPos, yPos) {}

		virtual void update() override;
	};
}