#pragma once

#include "Entity.hpp"
#include <vector>
#include <map>

using EntityVec = std::vector<std::shared_ptr<Entity>>;
using EntityMap = std::map<std::string, EntityVec>;

class EntityManager
{
	EntityVec	 m_entities;
	EntityVec	 m_entitiesToAdd;		//for delayed effects concept implentation
	EntityMap	 m_entityMap;
	size_t		 m_totalEntities = 0;


	void removeDeadEntities(EntityVec& vec)
	{
		//TODO : remove all dead entities from the input vector
		//std::remove_if
		//	this is called by the update() function
		vec.erase(std::remove_if(vec.begin(), vec.end(), [](std::shared_ptr<Entity>& e)
			{
				return !(e->isActive());
			}), vec.end());
	}

public:
	
	EntityManager() = default;

	//.cpp functions
	void update(); 


	//.hpp functions


	std::shared_ptr<Entity> addEntity(const std::string& tag)
	{
		auto entity = std::shared_ptr<Entity>(new Entity(m_totalEntities++, tag));
		m_entitiesToAdd.push_back(entity);
		//m_entityMap[tag].push_back(entity);
		return entity;
	}

	const EntityVec& getEntities()
	{
		return m_entities;
	}

	const EntityVec& getEntities(const std::string& tag)
	{
		if (m_entityMap.find(tag) == m_entityMap.end())
		{
			m_entityMap[tag] = EntityVec();
		}
		return m_entityMap[tag];
	}

};