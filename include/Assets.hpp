#pragma once

#include<SFML\Graphics.hpp>
#include<map>
#include<cassert>
#include<iostream>
#include<fstream>

class Animation; 

class Assets
{
	
	std::map<std::string, sf::Texture> m_textureMap;
	std::map<std::string, Animation> m_animationMap;
	std::map<std::string, sf::Font> m_fontMap;
	
	void addTexture(const std::string& textureName, const std::string& path, bool smooth = false);
	void addAnimation(const std::string& animationName, const std::string& textureName, size_t frames, size_t speed);
	void addFont(const std::string& fontName, const std::string& path);

	Assets() = default;

public:

	//singelton class instantiation
	static Assets& Instance()
	{
		static Assets assets;
		return assets;
	}

	
	
	
	const sf::Texture& getTexture(const std::string& textureName) const
	{
		auto it = m_textureMap.find(textureName);
		assert(it != m_textureMap.end());
		return it->second;
	}
	
	const Animation& getAnimation(const std::string& animationName) const
	{
		assert(m_animationMap.find(animationName) != m_animationMap.end());
		return m_animationMap.at(animationName);
	}
	
	const sf::Font& getFont(const std::string& fontName) const
	{
		auto it = m_fontMap.find(fontName);
		assert(it != m_fontMap.end());
		return it->second;
	}


	const std::map<std::string, sf::Texture>& getTextures() const
	{
		return m_textureMap;
	}

	const std::map<std::string, Animation>& getAnimations() const
	{
		return m_animationMap;
	}
	
	void loadFromFile(const std::string& path);
};