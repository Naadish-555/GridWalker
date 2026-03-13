#pragma once

#include "Entity.hpp"

namespace Physics
{
	///NOTE : vec2 was vec2f

	//if a point is inside entity or not
	bool IsInside(const Vec2& pos, std::shared_ptr<Entity> e)
	{
		return false;
	}

	// return if two lines intersect or not
	bool IsInteresect(const Vec& a, const Vec& b, const Vec& c, const Vec& d)
	{
		return false;
	}

	//returns if two entities collide or not
	bool IsCollision(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b)
	{
		return false;
	}



	Vec2 GetOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b)
	{
		//TODO : return the overlap rectangle size of the bounding boxes of entity a and b
		return Vec2(0, 0);
	}

	Vec2 GetPreviousOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b)
	{
		//TODO : return the previous overlap rectangle size of the bounding boxes of entity a and b
		// previous overlap uses entity's previous position
		return Vec2(0, 0);
	}


}