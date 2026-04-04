#pragma once

#include "Scene.hpp"
#include "Assets.hpp"
#include "Grid.hpp"
//Entity.h


#include "imgui.h"
#include "imgui-SFML.h"
#include "imguiThemes.h"
#include <memory>

typedef std::map<std::string, std::shared_ptr<Scene>> SceneMap;

struct WindowConfig { int WW = 1920, WH = 1080, R = 25, G = 25, B = 25, FL = 60, FS = 0; };

class GameEngine
{
protected:
	sf::RenderWindow m_window;
	std::string		 m_currentScene;
	SceneMap		 m_SceneMap;
	size_t			 m_simulationSpeed = 1;
	sf::Clock		 m_deltaClock;
	bool			 m_running = true;
	float			 m_fps = 0;
	float			 m_dt = 0;

	WindowConfig	 m_windowConfig;

	void init(const std::string& path);
	void update();
	void sUserInput();

	std::shared_ptr<Scene> currentScene() { return m_SceneMap[m_currentScene]; }

public:
	GameEngine(const std::string& path);

	void changeScene(const std::string& sceneName, std::shared_ptr<Scene> scene, bool endCurrentScene = false);
	void run();
	void quit() { m_running = false ; }

	sf::RenderWindow& window() { return m_window; }
	bool isRunning() { return m_running && m_window.isOpen(); }
	const float getFps() const { return m_fps; }
	const float getDeltaTime() const { return m_dt; }
};










//
//struct WindowConfig { int WW = 1920, WH = 1080, R = 25, G = 25, B = 25 , FL = 60, FS = 0; };
//struct BoidsConfig { int BTS = 200, MN = 30;float VD = 45.0f, AD = 15.0f, MaxBS = 3.0f, MinBS = 0.1f, SS = 0.01f; };
//struct FlockConfig { float FSV = 1.5f, FAV = 1.0f, FCV = 1.0f; };
//struct PredatorConfig { int LTM = 2; float FOV = 150.0f, FR = 150.0f, FS = 3.0f, LR = 150.0f, PS = 150.0f ; };
//struct FontConfig	{ int S = 24, R = 255, G =255 , B=255; std::string F = ""; };
//
//class Game
//{
//	sf::RenderWindow	m_window;			
//	EntityManager		m_entities;						//Vector of entities to maintain
//	sf::Font			m_font;							//the font which will be use to draw
//	sf::Text			m_text;							//the score text to be drawn to the screen
//	sf::Clock			m_deltaClock;					//for imgui 
//	WindowConfig		m_windowConfig;
//	BoidsConfig			m_boidConfig;
//	PredatorConfig		m_predatorConfig;
//	FlockConfig			m_flockConfig;
//	FontConfig			m_fontConfig;
//	int					m_score = 0;
//	int					m_currentFrame = 0;
//	int					m_lastBoidSpawnTime = 0;
//	bool				m_paused = false;				//whether we update game logic
//	bool				m_running = false;				//if game is running
//
//	
//	//boids specific vars
//	Grid				m_grid;
//
//	int					m_boidsToSpawn = 200;
//	int					m_maxNeighbours = 30;			//max neighbours a boid can have within the visual range
//
//	float				m_seperationValue	= 1.5f;
//	float				m_alignmentValue	= 1.0f;
//	float				m_cohesionValue		= 1.0f;
//
//	float				m_visionDistance	= 45.0f;
//	float				m_avoidDistance		= 15.0f;
//	float				m_maxBoidSpeed		= 3.0f;
//	float				m_minBoidSpeed		= 0.1f;
//	float				m_steeringStrength	= 0.01f;
//
//	bool				m_drawDebugLines = false;
//	bool				m_drawBoids = true;
//	bool				m_drawGrid = false;
//
//	sf::VertexArray		m_gridLines;
//
//	std::vector<CTransform>		m_boidsTfCache;			//used in sFlocking to improve performance (fetching from m_entities every frame very slow)
//	std::vector<int>			m_neighbourCache;		
//
//
//	//Predator specific vars
//
//	int					m_predatorLoopTraverseMode = 2;
//
//	float				m_predatorTimeAccumulator = 0.0f;
//	float				m_predatorFOV   = 150.0f;
//	float				m_fearRadius	= 150.0f;
//	float				m_fearStrength	= 3.0f;
//	float				m_predatorDesiredLoopRadius = 150.0f;
//	float				m_predatorCurrentLoopRadius = 150.0f;
//	float				m_predatorSpeed = 150.0f;
//
//	bool				m_predatorActive = false;
//	bool				m_drawPredator = true;
//
//	const char*			m_predatorTraverseList[3] = { "Oval", "Figure-8 Loop", "Spiral" };
//
//	void init(const std::string& config);				//intializing game state with a config file path
//	void setPaused(bool paused);						//pause the game
//
//
//	void sMovement(float dt);							//System : Entity position / movement update
//	void sUserInput();									//System : User Input
//	void sRender();										//System : Render / Drawing
//	void sCollision();									//System : Collisions
//	void sGUI();										//System : ImGUI interface
//
//
//	//Boids systems
//	void sBoidSpawner(int boidsToSpawn);				//System : boids Spawner 
//	void sFlocking();									//System : boids flocking
//
//
//
//	//Boids functions
//	void spawnBoid();
//	void resetSimultaion();
//	void drawGrid();
//
//	void spawnPredator();
//
//	void defaultBoidParameters();
//	void defaultFlockParameters();
//	void defaultPredatorParameters();
//
//
//
//public:
//	
//	Game(const std::string& config);					//constructor takes in game config
//
//	void run();
//};