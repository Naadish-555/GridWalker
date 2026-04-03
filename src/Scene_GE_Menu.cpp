#include "GameEngine.hpp"
#include "Scene_GE_Menu.h"
#include "Scene_Platformer.h"
//load all other includes for other scenes for loading

#include<iostream>

Scene_GE_Menu::Scene_GE_Menu(GameEngine* gameEngine) 
	: Scene(gameEngine)
{
	init();
}

void Scene_GE_Menu::init()
{
	m_game->window().setView(m_game->window().getDefaultView());
	
	m_menuStrings.emplace_back("Platformer");
	m_menuStrings.emplace_back("Boids Sim");
	m_menuStrings.emplace_back("Poly Wars");
	m_menuStrings.emplace_back("Exit");

	
	m_menuText.setFont(Assets::Instance().getFont("Bills"));

	m_levelPaths.emplace_back( "D:/SFML C++ Projects/Platformer/resources/levels/level.txt");

	//inputs for menu scene
	registerAction(sf::Keyboard::W, "UP");
	registerAction(sf::Keyboard::S, "DOWN");
	registerAction(sf::Keyboard::Enter, "SELECT");
}

void Scene_GE_Menu::update()
{

}

void Scene_GE_Menu::onEnd()
{
	m_game->quit();
}

void Scene_GE_Menu::sDoAction(const Action& action)
{
	if (action.type() == "START")
	{
		if (action.name() == "SELECT")
		{
			if (m_menuStrings[m_currentMenuIndex] == "Platformer")
			{
				m_game->changeScene("PLATFORMER", std::make_shared<Scene_Platformer>(m_game, m_levelPaths[m_currentMenuIndex]));;
			}
			else if (m_menuStrings[m_currentMenuIndex] == "Boids Sim")
			{
				//m_game->changeScene("PLATFORMER", std::make_shared<Scene_Boids_Sim>(m_game, m_levelPaths[m_currentMenuIndex]));;
			}
			else if (m_menuStrings[m_currentMenuIndex] == "Poly Wars")
			{
				//m_game->changeScene("PLATFORMER", std::make_shared<Scene_Poly_Wars>(m_game, m_levelPaths[m_currentMenuIndex]));;
			}
			else if (m_menuStrings[m_currentMenuIndex] == "Exit")
			{
				onEnd();
			}
		}

		else if (action.name() == "UP")
		{
			m_currentMenuIndex = (m_currentMenuIndex > 0) ? --m_currentMenuIndex : m_menuStrings.size() - 1;
		}
		else if (action.name() == "DOWN")
		{
			m_currentMenuIndex = (m_currentMenuIndex + 1) % m_menuStrings.size();
		}
		
	}
}


void Scene_GE_Menu::sRender()
{
	auto& window = m_game->window();

	//clear window with the intended bg color
	window.clear(sf::Color(20, 22, 26));

	//setup title tet


	float posX = window.getSize().x / 2.0f - m_menuText.getLocalBounds().width / 2.0f;
	float posY = window.getSize().y / 2.0f - m_menuText.getLocalBounds().height / 2.0f;
	m_menuText.setPosition(posX, posY);
	//window.draw(m_menuText);

	//selectable menu options
	m_menuText.setCharacterSize(30);
	m_menuTextBackground.setSize(sf::Vector2f(200, 75));
	m_menuTextBackground.setFillColor(sf::Color(158, 97, 22));

	for (int i = 0; i < m_menuStrings.size(); i++)
	{
		posX = width() /2.0f - m_menuTextBackground.getSize().x/2.0f;
		posY = (height() / 2.0f) / 2.0f + (float)i * 100;
		m_menuTextBackground.setPosition(posX, posY);

		if (m_currentMenuIndex == i)
		{
			m_menuText.setString(m_menuStrings[i]);
			m_menuText.setFillColor(sf::Color::Black);

			//the bounding box positino of sf::text object is not (0,0)
			//To correct his offset, subtract the local bounding rectangles position
			posX = m_menuTextBackground.getPosition().x + (m_menuTextBackground.getLocalBounds().width) / 2.0f - (m_menuText.getLocalBounds().width / 2.0f) - m_menuText.getLocalBounds().left;
			posY = m_menuTextBackground.getPosition().y+ (m_menuTextBackground.getLocalBounds().height) / 2.0f - (m_menuText.getLocalBounds().height / 2.0f) - m_menuText.getLocalBounds().top;
			m_menuText.setPosition(posX, posY);

			//use outline of rectangle shape as a highlight to show the option would be selected
			m_menuTextBackground.setOutlineColor(sf::Color::Red);
			m_menuTextBackground.setOutlineThickness(3);
		}
		else
		{
			m_menuText.setString(m_menuStrings[i]);
			m_menuText.setFillColor(sf::Color::White);
			posX = m_menuTextBackground.getPosition().x + (m_menuTextBackground.getLocalBounds().width) / 2.0f - (m_menuText.getLocalBounds().width / 2.0f) - m_menuText.getLocalBounds().left;
			posY = m_menuTextBackground.getPosition().y + (m_menuTextBackground.getLocalBounds().height) / 2.0f - (m_menuText.getLocalBounds().height / 2.0f) - m_menuText.getLocalBounds().top;

			m_menuText.setPosition(posX, posY);

			m_menuTextBackground.setOutlineColor(sf::Color(150, 150, 150));
			m_menuTextBackground.setOutlineThickness(1);
		}

		window.draw(m_menuTextBackground);
		window.draw(m_menuText);
	}
}