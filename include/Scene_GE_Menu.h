#pragma once

#include"Scene.hpp"
#include<vector>

class Scene_GE_Menu : public Scene
{
protected:
	size_t						m_currentMenuIndex = 0;
	sf::Font					m_font; //temp
	sf::Text					m_menuText;
	sf::RectangleShape			m_menuTextBackground;
	std::vector<std::string>	m_menuStrings;
	std::vector<std::string>	m_levelPaths;

	void init();
	void update();
	void onEnd();

public:
	Scene_GE_Menu() = default;
	Scene_GE_Menu(GameEngine* gameEngine = nullptr);
	
	void sRender();
	void sDoAction(const Action& action);
};
