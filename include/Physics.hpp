#pragma once

#include "Entity.hpp"


namespace Physics
{
	///NOTE : vec2 was vec2f

	//if a point is inside entity or not
	bool IsInside(const Vec2& pos, std::shared_ptr<Entity> e)
	{
		Vec2 topLeft = e->get<CTransform>().pos ;
		Vec2 widthHeight = e->get<CBoundingBox>().size;
		if (pos.x > topLeft.x && pos.x < topLeft.x + widthHeight.x && pos.y >topLeft.y && pos.y < topLeft.y + widthHeight.y)
		{
			return true;
		}
		return false;
	}

	// return if two lines intersect or not
	bool IsInteresect(const Vec2& a, const Vec2& b, const Vec2& c, const Vec2& d)
	{

		return false;
	}

	



	Vec2 GetOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b)
	{
		//TODO : return the overlap rectangle size of the bounding boxes of entity a and b
		if (!a->has<CBoundingBox>() || !b->has<CBoundingBox>()) { return Vec2(0, 0); }

		Vec2 aHalfWH = a->get<CBoundingBox>().halfSize;
		Vec2 bHalfWH = b->get<CBoundingBox>().halfSize;

		Vec2 aP = a->get<CTransform>().pos + a->get<CBoundingBox>().offset;
		Vec2 bP = b->get<CTransform>().pos + b->get<CBoundingBox>().offset;

		Vec2 delta = Vec2(std::abs(aP.x - bP.x), std::abs(aP.y - bP.y));
		float ox = aHalfWH.x + bHalfWH.x - delta.x;
		float oy = aHalfWH.y + bHalfWH.y - delta.y;

		return Vec2(ox, oy);
	}

	Vec2 GetPreviousOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b)
	{
		//TODO : return the previous overlap rectangle size of the bounding boxes of entity a and b
		// previous overlap uses entity's previous position
		if (!a->has<CBoundingBox>() || !b->has<CBoundingBox>())  { return Vec2(0, 0); }

		Vec2 aHalfWH = a->get<CBoundingBox>().halfSize;
		Vec2 bHalfWH = b->get<CBoundingBox>().halfSize;

		Vec2 aP = a->get<CTransform>().prevPos + a->get<CBoundingBox>().offset;
		Vec2 bP = b->get<CTransform>().prevPos + b->get<CBoundingBox>().offset;

		Vec2 delta = Vec2(std::abs(aP.x - bP.x), std::abs(aP.y - bP.y));
		float ox = aHalfWH.x + bHalfWH.x - delta.x;
		float oy = aHalfWH.y + bHalfWH.y - delta.y;

		return Vec2(ox, oy);
	}

	//returns if two entities collide or not
	bool IsCollision(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b)
	{
		if (!a->has<CBoundingBox>() || !b->has<CBoundingBox>()) { return false; }

		auto& aTf = a->get<CTransform>();
		auto& aBb = a->get<CBoundingBox>();

		Vec2 aTL = aTf.pos - aBb.halfSize + aBb.offset ;
		Vec2 aWH = aBb.size;

		auto& bTf = b->get<CTransform>();
		auto& bBb = b->get<CBoundingBox>();
		Vec2 bTL = bTf.pos - bBb.halfSize + bBb.offset;
		Vec2 bWH = bBb.size;

		if (aTL.x < bTL.x + bWH.x && bTL.x < aTL.x + aWH.x)
		{
			if (aTL.y < bTL.y + bWH.y && bTL.y < aTL.y + aWH.y)
			{
				return true;
			}
		}

		return false;

		///alternate solution

		/*if (!a->has<CBoundingBox>() || !b->has<CBoundingBox>()) { return false; }
		Vec2 overlap = GetOverlap(a, b);
		return (overlap.x > 0 && overlap.y > 0);*/
	}
}