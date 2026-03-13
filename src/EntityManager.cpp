#include "EntityManager.hpp"


void EntityManager::update()
{
	//TODO : add entities from m_entitiesToAdd the proper location(s)
	//		- add them to the vector of all entities
	//		- add them to the vector inside the map, with the tag as a key

	for (auto& e : m_entitiesToAdd)
	{
		m_entities.push_back(e);
		m_entityMap[e->tag()].push_back(e);
	}

	m_entitiesToAdd.clear();

	//	remove dead entities from the vector of all entities
	removeDeadEntities(m_entities);

	//remove dead entities from each vector in the entity map
	//C++17 way of iterating through [key,value] pairs in a map
	for (auto& [tag, entityVec] : m_entityMap)
	{
		removeDeadEntities(entityVec);
	}
}
