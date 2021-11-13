#include "chpch.hpp"

#include "Actor.hpp"

namespace cp
{
	Actor::Actor(const std::string& imgPath) : SSprite(imgPath)
	{
	}


	Actor::Actor(const std::string& imgPath, const float xPos, const float yPos) : SSprite(imgPath, xPos, yPos)
	{
	}


	void Actor::update(float dt)
	{
		SSprite::update(dt);
	}


	void Actor::reset()
	{
	}
}
