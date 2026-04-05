#pragma once

#include "Vec2.hpp"
#include "Animation.hpp"
#include "Assets.hpp"

class Component
{
public:
	bool exists = false;	
};

class CTransform : public Component
{
public:
	Vec2 pos		= { 0.0f, 0.0f };
	Vec2 prevPos	= { 0.0f, 0.0f };
	Vec2 scale		= { 1.0f, 1.0f };
	Vec2 velocity	= { 0.0f, 0.0f };
	float angle		= 0;

	CTransform() = default;
	CTransform(const Vec2& p)
		: pos(p) {}
	CTransform(const Vec2& p, const Vec2& v, const Vec2& sc, float a)
		:pos(p), prevPos(p), velocity(v), scale(sc), angle(a) {}
};


class CMesh : public Component
{
public:
	float size = 10.0f;						//length of boid
	float width = 7.0f;						//width of rear

	sf::Color color = sf::Color::White;

	CMesh() = default;

	CMesh(float s, float w, sf::Color c)
		:size(s), width(w), color(c) {}
};

class CShape : public Component
{
public:
	/*sf::CircleShape circle;

	CShape() = default;
	CShape(float radius, int points, const sf::Color& fill, const sf::Color& outline, float thickness)
		: circle(radius, points)
	{
		circle.setFillColor(fill);
		circle.setOutlineColor(outline);
		circle.setOutlineThickness(thickness);
		circle.setOrigin(radius, radius);
	}*/

	sf::ConvexShape polygon;

	CShape()
	{
		polygon.setPointCount(3);
		polygon.setPoint(0, sf::Vector2f(10.0f, 0.0f));
		// Bottom Right
		polygon.setPoint(1, sf::Vector2f(-10.0f, 7.0f));
		// Bottom Left
		polygon.setPoint(2, sf::Vector2f(-10.0f, -7.0f));

		//polygon.setOrigin(sf::Vector2f(polygon.getLocalBounds().width / 2, polygon.getLocalBounds().height / 2));
		polygon.setFillColor(sf::Color::White);
		polygon.setOutlineColor(sf::Color::Black);
		polygon.setOutlineThickness(1.0f);
	}

};

class CCollision : public Component
{
public:
	float radius = 0;

	CCollision() = default;
	CCollision(float r)
		: radius(r) {}
};

class CScore : public Component
{
	//for assigning points to the given enemy e.g 100,200,etc when it dies 
public:
	int score = 0;

	CScore() = default;
	CScore(int s)
		: score(s) {}
};

class CLifespan : public Component
{
public:
	float remaining = 0; //lifespan remaing on entity
	float total	  = 0; //total amount of lifespan

	CLifespan() = default;
	CLifespan(float total)
		:remaining(total), total(total){}
};

class CInput : public Component
{
public:
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
	bool jump = false;
	bool shoot = false;
	bool canShoot = true;

	CInput() = default;
};

class CBoundingBox : public Component
{
public:
	Vec2 size;
	Vec2 halfSize;
	Vec2 offset = Vec2(0,0);			
	CBoundingBox() = default;
	CBoundingBox(const Vec2& s)
		: size(s), halfSize(s.x / 2, s.y / 2) {}
	CBoundingBox(const Vec2& s, const Vec2& os)
		: size(s), halfSize(s.x / 2, s.y / 2), offset(os) {}
};

class CAnimation : public Component
{
public:
	Animation animation;
	bool repeat = false;
	CAnimation() = default;
	CAnimation(const Animation& anim, bool r)
		: animation(anim), repeat(r) {}
};

class CGravity : public Component
{
public:
	float gravity = 9.8;
	bool isGrounded = false;
	CGravity() = default;
	CGravity(float g)
		: gravity(g) {}
};

class CState : public Component
{
public:
	std::string state = "Jump";

	CState() = default;
	CState(const std::string& s)
		: state(s) {}
};

class CBoid : public Component
{
public:
	
	//will be used further for implementing species but right now used only for the , has (exists) function
	CBoid() = default;
};


static_assert(std::is_default_constructible_v<CTransform>);
static_assert(std::is_default_constructible_v<CMesh>);
static_assert(std::is_default_constructible_v<CShape>);
static_assert(std::is_default_constructible_v<CAnimation>);
static_assert(std::is_default_constructible_v<CBoundingBox>);
static_assert(std::is_default_constructible_v<CBoid>);
static_assert(std::is_default_constructible_v<CCollision>);
static_assert(std::is_default_constructible_v<CGravity>);
static_assert(std::is_default_constructible_v<CInput>);
static_assert(std::is_default_constructible_v<CLifespan>);