#include "Scene.hpp"
#include "GameEngine.hpp"


size_t Scene::width() const
{
	return m_game->window().getSize().x;
}

size_t Scene::height() const
{
	return m_game->window().getSize().y;
}

void Scene::drawLine(const Vec2& p1, const Vec2& p2)
{
	sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(p1.x,p1.y)),
		sf::Vertex(sf::Vector2f(p2.x,p2.y))
	};
	m_game->window().draw(line, 2, sf::Lines);
}

void Scene::simulate(const size_t frames)
{
	for (size_t i = 0; i < frames; i++)
	{
		update();
	}
}