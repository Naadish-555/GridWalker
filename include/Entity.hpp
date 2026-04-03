#pragma once

#include "Components.hpp"
#include <memory>
#include <string>
#include <tuple>

using ComponentTuple = std::tuple<
	CTransform,
	CAnimation,
	CBoundingBox,
	CGravity,
	CState,
	CMesh,
	//CShape,
	CCollision,
	CInput,
	CScore,
	CLifespan,
	CBoid
>;	

class Entity
{
	friend class EntityManager;

	bool		m_active	= true;
	size_t		m_id		= 0;
	std::string	m_tag		= "default";
	ComponentTuple m_components;
	

	//constructor and destructor
	Entity(const size_t id, const std::string& tag)
		:m_id(id)
		, m_tag(tag)
	{
	}


public:

	template <typename T>
	bool has()	const
	{
		return get<T>().exists;
	}

	template <typename T, typename... TArgs>
	T& add(TArgs&&... mArgs)
	{
		auto& component = get<T>();
		component = T(std::forward<TArgs>(mArgs)...);
		component.exists = true;
		return component;
	}

	template <typename T>
	T& get()
	{
		return std::get<T>(m_components);
	}

	template <typename T>
	const T& get() const
	{
		return std::get<T>(m_components);
	}

	template <typename T>
	void remove()
	{
		get<T>() = T();
	}

	//member access functions

	bool isActive() const
	{
		return m_active;
	}

	const std::string& tag() const
	{
		return m_tag;
	}

	const size_t id() const
	{
		return m_id;
	}

	void destroy()
	{
		m_active = false;
	}

	sf::FloatRect getBounds(const Vec2& pos, float size)
	{
		// Return a square centered on the boid
		return sf::FloatRect(
			pos.x - size, // Left
			pos.y - size, // Top
			size * 2,     // Width
			size * 2      // Height
		);
	}

	
};