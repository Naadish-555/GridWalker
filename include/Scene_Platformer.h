#pragma once

#include "Scene.hpp"
#include "EntityManager.hpp"

class Scene_Platformer : public Scene
{
	struct PlayerConfig
	{
		float X, Y, CX, CY, SPEED, MAXSPEED, JUMP, GRAVITY;
		std::string weapon;
	};

protected:
	std::shared_ptr<Entity>		m_player;
	std::string					m_levelPath;
	PlayerConfig				m_playerConfig;
	bool						m_drawTextures = true;
	bool						m_drawCollision = false;
	bool						m_drawGrid = false;
	const Vec2					m_gridSize = { 64,64 };

protected : 

	void init(const std::string& levelPath);

	void loadLevel(const std::string& fileName);

	Vec2 gridToMidPixel(float gridX, float gridY, std::shared_ptr<Entity> entity);

	void spawnPlayer();

	void spawnLevelTiles(std::string& tag, std::string& animName , float gridX, float gridY);

	void spawnBullet();

	void update();

	void onEnd();

public:

	Scene_Platformer(GameEngine* gameEngine, const std::string& levelPath);
	
	void sDoAction(const Action& action);
	void sRender();
	
	void sMovement();
	void sLifeSpan();
	void sCollision();
	void sAnimation();
	void sGUI();
	void sEnemySpawner();
	void sDebug();
	
	//drawLine() but already implemented in Scene.hpp	

};

