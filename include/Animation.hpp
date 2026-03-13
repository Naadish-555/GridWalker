#pragma once

#include "Vec2.hpp"
#include <vector>
#include <SFML/Graphics.hpp>

class Animation
{
	sf::Sprite	m_sprite;
	size_t		m_frameCount	= 1;	//total number of frames of animation
	size_t		m_currentFrame	= 0;	//current frame of animation being played
	size_t		m_gameFrame		= 0;	//the specific game frame the animation was created on 
	size_t		m_speed			= 0;	//the speed of duration to play this animation
	Vec2		m_size			= {1,1}; //size of animation frame
	std::string m_name			= "none";

public:

	Animation() = default;

	Animation(const std::string& name, const sf::Texture& t)
		: Animation(name, t, 1, 0) 
	{ }

	Animation(const std::string& name, const sf::Texture& t, size_t frameCount, size_t speed)
		: m_name(name)
		, m_sprite(t)
		, m_frameCount(frameCount)
		, m_currentFrame(0)
		, m_speed(speed)
	{
		m_size = Vec2((float)t.getSize().x / frameCount, (float)t.getSize().y);
		m_sprite.setOrigin(m_size.x / 2.0f, m_size.y / 2.0f);
		m_sprite.setTextureRect(sf::IntRect((int)std::floor(m_currentFrame) * (int)m_size.x, 0, (int)m_size.x, (int)m_size.y));

	}

	void update()
	{
		//if spede is zero then there is only one animation frame and no other frames to switch to
		if (m_speed != 0)
		{
			m_currentFrame++;
			size_t animFrame = (m_currentFrame / m_speed) % m_frameCount;
			m_sprite.setTextureRect(sf::IntRect((int)std::floor(animFrame) * (int)m_size.x, 0, (int)m_size.x, (int)m_size.y));
		}
	}

	bool hasEnded() const
	{
		if (m_currentFrame == m_frameCount * m_speed)
			return true;
		return false;
	}
	
	const std::string& getName() const
	{
		return m_name;
	}

	const Vec2& getSize() const
	{
		return m_size;
	}
	
	sf::Sprite& getSprite()
	{
		return m_sprite;
	}
	
	const sf::Sprite& getSprite() const
	{
		return m_sprite;
	}
	

};