#include "Scene_Platformer.h"
#include "Scene_GE_Menu.h"
#include "Physics.hpp"
#include "Assets.hpp"
#include "GameEngine.hpp"
#include "Components.hpp"
#include "Action.hpp"

Scene_Platformer::Scene_Platformer(GameEngine* gameEngine, const std::string& levelPath)
	: Scene(gameEngine)
	, m_levelPath(levelPath)
{
	init(m_levelPath);
}


void Scene_Platformer::init(const std::string& levelPath)
{
	registerAction(sf::Keyboard::Scancode::W,		"UP");
	registerAction(sf::Keyboard::Scancode::A,		"LEFT");
	registerAction(sf::Keyboard::Scancode::S,		"DOWN");
	registerAction(sf::Keyboard::Scancode::D,		"RIGHT");
	registerAction(sf::Keyboard::Scancode::K,		"SHOOT");
	registerAction(sf::Keyboard::Scancode::J,		"JUMP");

	registerAction(sf::Keyboard::Scancode::P,		"PAUSE");
	registerAction(sf::Keyboard::Scancode::M,		"QUIT");
	registerAction(sf::Keyboard::Scancode::T,		"TOGGLE_TEXTURE");
	registerAction(sf::Keyboard::Scancode::B,		"TOGGLE_COLLISION");
	registerAction(sf::Keyboard::Scancode::G,		"TOGGLE_GRID");

	
	//TODO : Register all other gameplay actions

	loadLevel(levelPath);
}

void Scene_Platformer::loadLevel(const std::string& fileName)
{
	//reset the entitymanager eveerytime we load a level
	m_entityManager = EntityManager();

	std::ifstream fin(fileName);
	std::string input, tag , animName;
	float gridX = 0, gridY = 0;
	while (fin.good())
	{
		fin >> input;
		std::cout << "Token read [" << input << " ]" << std::endl;
		if (input == "Tile" || input == "Dec")
		{
			tag = input;
			fin >> animName >> gridX >> gridY;
			spawnLevelTiles(tag, animName, gridX, gridY);
		}
		else if (input == "Player")
		{
			fin >> m_playerConfig.X >> m_playerConfig.Y >> m_playerConfig.CX >> m_playerConfig.CY >> m_playerConfig.SPEED >> m_playerConfig.MAXSPEED >> m_playerConfig.JUMP >> m_playerConfig.GRAVITY >> m_playerConfig.weapon;
		}
	}
	//TODO: read in the level file and the appropriate entities
	//use m_playerConfig to store player properties


	//NOTE : below code is sample code for setting up and using entities , remove it later
	spawnPlayer();

	//some sample entities
	auto brick = m_entityManager.addEntity("Tile");
	//NOTE : always add the CAnimation component first so that the gridToMidPixel can al
	brick->add<CAnimation>(Assets::Instance().getAnimation("Brick"), true);
	brick->add<CTransform>(gridToMidPixel(1, 3, brick));
	//NOTE : final code should use position from aseets.txt and utilise gridToMidPixel function
	//brick->add<CTransform>(gridToMidPixel(gridX,gridY,brick));

	if (brick->get<CAnimation>().animation.getName() == "Brick")
	{
		//could be a good way of identifying entity tile brick
	}

	auto block = m_entityManager.addEntity("Tile");
	block->add<CAnimation>(Assets::Instance().getAnimation("Box"), true);
	block->add<CTransform>(Vec2(224, 550));
	
	auto block2 = m_entityManager.addEntity("Tile");
	block2->add<CAnimation>(Assets::Instance().getAnimation("Box"), true);
	block2->add<CTransform>(gridToMidPixel(3,6,block2));

	//addeed a bounding box, will show up if press the 'B' key
	block->add<CBoundingBox>(Assets::Instance().getAnimation("Box").getSize());

	auto question = m_entityManager.addEntity("Tile");
	question->add<CAnimation>(Assets::Instance().getAnimation("MetalBox"), true);
	question->add<CTransform>(Vec2(352, 480));

}

Vec2 Scene_Platformer::gridToMidPixel(float gridX, float gridY, std::shared_ptr<Entity> entity)
{
	
	//TODO : This function takes in a grid (x,y) position and an entity
	//return a vec2 indicating where the center posistion of the entity should be
	//Vec2 gridPos = Vec2((gridX / m_gridSize.x) ,  gridY / m_gridSize.y); //bottom left
	auto halfSize = entity->get<CAnimation>().animation.getSize() / 2.0f;
	float x = (gridX * m_gridSize.x) + halfSize.x;
	float y = (height() - (gridY * m_gridSize.y)) - halfSize.y;
	return Vec2(x , y);
}

void Scene_Platformer::spawnPlayer()
{
	//check to see if a player already exists before adding a new one
	//if it already exists just overwrite the values of existing one
	if (!m_player) { m_player = m_entityManager.addEntity("Player"); }

	//here is a sample player entity which you can use to construct other entities
	m_player->add<CAnimation>(Assets::Instance().getAnimation("Idle"), true);
	m_player->add<CTransform>(gridToMidPixel(m_playerConfig.X,m_playerConfig.Y,m_player));
	m_player->add<CBoundingBox>(Vec2(m_playerConfig.CX, m_playerConfig.CY));
	m_player->add<CState>("Idle");
	m_player->add<CGravity>(m_playerConfig.GRAVITY);
	m_player->add<CInput>();


	//TODO :  add remaining components to the player

}

void Scene_Platformer::spawnLevelTiles(std::string& tag, std::string& animName, float gridX, float gridY)
{
	if (tag == "Tile")
	{
		auto tile = m_entityManager.addEntity(tag);
		//Vec2 pos = gridToMidPixel(gridX, gridY, tile);
		
		tile->add<CAnimation>(Assets::Instance().getAnimation(animName), true);
		tile->add<CTransform>(gridToMidPixel(gridX, gridY, tile));
		tile->add<CBoundingBox>(Assets::Instance().getAnimation(animName).getSize());

		//tile->get<CTransform>().prevPos = pos;
	}
	else if (tag == "Dec")
	{
		auto dec = m_entityManager.addEntity(tag);
		//Vec2 pos = gridToMidPixel(gridX, gridY, dec);
		dec->add<CAnimation>(Assets::Instance().getAnimation(animName), true);
		dec->add<CTransform>(gridToMidPixel(gridX, gridY, dec));
		
		//dec->get<CTransform>().prevPos = pos;
	}
}

void Scene_Platformer::spawnBullet()
{
	//TODO : reuse function from poly wars
	// make sure bullet goes in dxn the player is facing
	auto bullet = m_entityManager.addEntity("Bullet");
	auto& playerTf = m_player->get<CTransform>();

	float bOffset = 10.0f;
	float bSpeed = 15.0f;


	bullet->add<CAnimation>(Assets::Instance().getAnimation("BusterGolden"), true);
	bullet->add<CTransform>(Vec2(playerTf.pos.x, playerTf.pos.y + bOffset));
	bullet->add<CBoundingBox>(Assets::Instance().getAnimation("BusterGolden").getSize());
	
	auto& bulletTf = bullet->get<CTransform>();
	bulletTf.velocity.x = playerTf.scale.x * bSpeed;
}


void Scene_Platformer::onEnd()
{
	//TODO : when the scene ends, change back to MENU scene
	// use m_game.changeScene();
	m_game->changeScene("MENU", std::make_shared<Scene_GE_Menu>(m_game),true);
}

void Scene_Platformer::update()
{
	m_entityManager.update();

	//TODO : implement pause functionality

	sMovement();
	sLifeSpan();
	sCollision();
	sAnimation();
	sGUI();
	sRender();

}



void Scene_Platformer::sDoAction(const Action& action)
{
	if (action.type() == "START")
	{

		//player inputs
		if (action.name() == "UP")						{ m_player->get<CInput>().up = true; }
		else if (action.name() == "LEFT")				{ m_player->get<CInput>().left = true; }
		else if (action.name() == "DOWN")				{ m_player->get<CInput>().down = true; }
		else if (action.name() == "RIGHT")				{ m_player->get<CInput>().right = true; }
		else if (action.name() == "JUMP")				{ m_player->get<CInput>().jump  = true; }
		else if (action.name() == "SHOOT")				{ m_player->get<CInput>().shoot = true; }
		//debug
		else if(action.name() == "TOGGLE_TEXTURE")		{ m_drawTextures = !m_drawTextures ;}
		else if(action.name() == "TOGGLE_COLLISION")	{ m_drawCollision = !m_drawCollision;}
		else if(action.name() == "TOGGLE_GRID")			{ m_drawGrid = !m_drawGrid; }
		else if(action.name() == "PAUSE")				{ setPause(!m_paused);}
		else if(action.name() == "QUIT")				{ onEnd(); }
		
	}
	else if (action.type() == "END")
	{
		//player inputs
		if (action.name() == "UP")						{ m_player->get<CInput>().up = false; }
		else if (action.name() == "LEFT")				{ m_player->get<CInput>().left = false; }
		else if (action.name() == "DOWN")				{ m_player->get<CInput>().down = false; }
		else if (action.name() == "RIGHT")				{ m_player->get<CInput>().right = false; }
		else if (action.name() == "JUMP")				{ m_player->get<CInput>().jump = false; }
		else if (action.name() == "SHOOT")				
		{ 
			m_player->get<CInput>().shoot = false; 
			m_player->get<CInput>().canShoot = true; 

		}

	}
}



void Scene_Platformer::sMovement()
{
	//TODO :
	// implement player movement/jumping based on its CInput component
	auto& input = m_player->get<CInput>();
	auto& tf = m_player->get<CTransform>();
	auto& state = m_player->get<CState>();
	auto& gravity = m_player->get<CGravity>();
	float accel = 0.5f;

	if (input.left)
	{
		if (tf.velocity.x > -m_playerConfig.SPEED)
			tf.velocity.x = -m_playerConfig.SPEED;
		else
			tf.velocity.x -= accel;

		if (tf.velocity.x <= m_playerConfig.MAXSPEED)
			tf.velocity.x = -m_playerConfig.MAXSPEED;

		tf.scale.x = -1;
	}
	else if (input.right)
	{
		if (tf.velocity.x < m_playerConfig.SPEED)
			tf.velocity.x = m_playerConfig.SPEED;
		else
			tf.velocity.x += accel;

		if (tf.velocity.x >= m_playerConfig.MAXSPEED)
			tf.velocity.x = m_playerConfig.MAXSPEED;
		tf.scale.x = 1;
	}
	else if (input.down)
	{
		tf.velocity.y = m_playerConfig.JUMP;
	}
	else
	{
		tf.velocity.x = 0;
		tf.velocity.y = 0;
	}
	if (input.jump && input.canJump)
	{
		tf.velocity.y = -m_playerConfig.JUMP;
	}
	if (!input.jump && tf.velocity.y < 0)
	{
		tf.velocity.y *= 0.5f;
	}

	


	if (input.shoot && input.canShoot)
	{
		spawnBullet();
		input.canShoot = false;
		std::cout << "prev pos : " << tf.prevPos.x << " , " << tf.prevPos.y << std::endl;
		std::cout << "current pos : " <<tf.pos.x << " , " << tf.pos.y << std::endl;
	}

	tf.prevPos = tf.pos;
	tf.pos += tf.velocity;
	tf.velocity.y += m_playerConfig.GRAVITY;
	if (tf.velocity.x != 0 )
	{
		state.state = "Run";
	}
	else if(tf.velocity.x == 0)
	{
		state.state = "Idle";
	}
		
	for (auto& e : m_entityManager.getEntities())
	{
		if (e->tag() == "Player") { continue; }

		e->get<CTransform>().prevPos = e->get<CTransform>().pos;
		e->get<CTransform>().pos += e->get<CTransform>().velocity;
	}

	// Implement gravity effect on player
	// Implement the maximum player speed in both X and Y directions
	// Note : Setting an entity's scale.x to -1/1 will make it face to left/right

}

void Scene_Platformer::sLifeSpan()
{
	//TODO : check lifespan of entities that have them and destroy if they go over their given life span
	// same as poly wars 
}

void Scene_Platformer::sCollision()
{
	//NOTE : SFML's (0,0) position is on TOP-LEFT corner
	//this means jummping will have a negative y-component
	//and gravity will have a positive y-component
	//Also something below else will have a y value grater than it
	//something above something else will have a y value less than it
	for (auto& t : m_entityManager.getEntities("Tile"))
	{

		//player collision
		if (Physics::IsCollision(m_player, t))
		{
			Vec2 ol = Physics::GetOverlap(m_player, t);
			Vec2 prevOl = Physics::GetPreviousOverlap(m_player, t);
		
			auto& pTf = m_player->get<CTransform>();
			auto& pBB = m_player->get<CBoundingBox>();
			auto& tTf = t->get<CTransform>();
			auto& tBB = t->get<CBoundingBox>();

			/*if(m_player->get<CInput>().up)
			{		
				std::cout << "current : " << ol.x << " , " << ol.y << std::endl;
				std::cout << "prev :  " << prevOl.x << " , " << prevOl.y << std::endl;
			}*/

			//collision resolution
			if (prevOl.y > 0)
			{

				if(pTf.pos.x  < tTf.pos.x ) //player is left
					pTf.pos.x -= ol.x;
				else
					pTf.pos.x += ol.x;
				pTf.velocity.x = 0;	
			}
			else if (prevOl.x > 0)
			{
				if (pTf.pos.y > tTf.pos.y) //player is below
					pTf.pos.y += ol.y;
				else
					pTf.pos.y -= ol.y;
				pTf.velocity.y = 0;
			}
		}

		//bullet collision
		for (auto& b : m_entityManager.getEntities("Bullet"))
		{
			if (!Physics::IsCollision(b, t)) { continue; }
			auto& tTf = t->get<CTransform>();
			std::cout << "bullet collision detected with tile" << std::endl;
			b->destroy();
			auto& explosion = m_entityManager.addEntity("Explosion");
			explosion->add<CAnimation>(Assets::Instance().getAnimation("Explosion"), false);
			explosion->add<CTransform>(Vec2(tTf.pos.x, tTf.pos.y));
			t->destroy();
		}
		
		
		
		
	}
	//TODO : Implement Physcics::GetOverlap() and use it inside this function

	//TODO ;: Implement bullet/tile collisions
	//Destroy the tile if it has a brick aimation
	//TODO : Implement player/tile collisions and resolutions
	//		update the CState component of the player to store if it is currently
	//		on the ground or in the air , this will be used by the animation system.


	//TODO: check to see if the player has fallen down a hole(y>height())
	//TODO : Don't let the player walk off the left side of the map
}

void Scene_Platformer::sAnimation()
{
	//TODO : complete the Animation class code first
	auto& currentState = m_player->get<CState>().state;
	auto& currentAnim = m_player->get<CAnimation>().animation.getName();


	//TODO : set the animation of the player based on its CState component
	//if the player's state has been set to running 
	//change its animation to a repeating a run animation
	//NOTE : adding a component that already exists simply overwrites it
	if (currentState == "Idle" && currentAnim != "Idle")
	{
		m_player->add<CAnimation>(Assets::Instance().getAnimation("Idle"), true);
	}
	else if (currentState == "Run" && currentAnim != "Run")
	{
		m_player->add<CAnimation>(Assets::Instance().getAnimation("Run"), true);
	}
	else if (currentState == "Jump" && currentAnim != "Jump")
	{
		m_player->add<CAnimation>(Assets::Instance().getAnimation("Jump"), true);
	}
	

	//TODO : for eachentity with an animation , call entity->get<CAnimation>().animation.update()
	//if the animation is not repeated and has ended , destroy the entity

	for (auto& e : m_entityManager.getEntities())
	{
		
	
		if (e->get<CAnimation>().repeat == false && e->get<CAnimation>().animation.hasEnded())
		{
			e->destroy();
		}
		else
		{
			e->get<CAnimation>().animation.update();
		}
		
	}
	
}

void Scene_Platformer::sGUI()
{
	ImGui::PushStyleColor(ImGuiCol_WindowBg, {});
	ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, {});
	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
	ImGui::PopStyleColor(2);
	

	ImGui::Begin("Scene Properties");
	if (ImGui::BeginTabBar("Debug"))
	{
		if (ImGui::BeginTabItem("Actions"))
		{
			for (const auto& [key, name] : getActionMap())
			{
				std::string ss = "START##" + name;
				std::string se = "END##" + name;

				if (ImGui::Button(ss.c_str()))
				{
					doAction(Action(name, "START"));
				}
				ImGui::SameLine();
				if (ImGui::Button(se.c_str()))
				{
					doAction(Action(name, "END"));
				}
				ImGui::SameLine();
				ImGui::Text("%s", name.c_str());
			}
			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Assets"))
		{
			if (ImGui::CollapsingHeader("Animations", ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::Indent();
				int count = 0;
				for (const auto& [name, anim] : Assets::Instance().getAnimations())
				{
					count++;
					ImGui::ImageButton(name.c_str(), anim.getSprite(), sf::Vector2f(32, 32));
					//TODO : fix this
					//if((count%6)!=0 && count != Assets::Instance().getAnimations().size())
				}
				ImGui::Unindent();
			}
			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}
	ImGui::End();
}


void Scene_Platformer::sRender()
{
	//color the bg darker so you know that the game is paused
	if (!m_paused) { m_game->window().clear(sf::Color(100, 100, 255)); }
	else { m_game->window().clear(sf::Color(50, 50, 150)); }

	sf::Font gridFont(Assets::Instance().getFont("Bills"));
	sf::Text gridText;
	gridText.setFont(gridFont);
	gridText.setCharacterSize(12);

	//set the viewport of the window to be centered on the player if its far enough right/left
	auto& pPos = m_player->get<CTransform>().pos;
	float windowCenterX = std::max(m_game->window().getSize().x / 2.0f, pPos.x);
	sf::View view = m_game->window().getView();
	view.setCenter({ windowCenterX, m_game->window().getSize().y - view.getCenter().y });
	m_game->window().setView(view);

	// draw all Entity textures/animations
	if (m_drawTextures)
	{
		for (auto e : m_entityManager.getEntities())
		{
			auto& transform = e->get<CTransform>();

			if (e->has<CAnimation>())
			{
				sf::Sprite sprite = e->get<CAnimation>().animation.getSprite();
				sprite.setRotation(transform.angle);
				sprite.setPosition(transform.pos.x,transform.pos.y);
				sprite.setScale(transform.scale.x,transform.scale.y );

				m_game->window().draw(sprite);

			}
		}

	}

	//draw all entity collision bounding boxes with a rectangle shape
	if (m_drawCollision)
	{
		for (auto e : m_entityManager.getEntities())
		{
			if (e->has<CBoundingBox>())
			{
				auto& box = e->get<CBoundingBox>();
				auto& transform = e->get<CTransform>();
				sf::RectangleShape rect;
				rect.setSize(sf::Vector2f(box.size.x - 1, box.size.y - 1));
				rect.setOrigin(sf::Vector2f(box.halfSize.x, box.halfSize.y));
				rect.setPosition(transform.pos.x,transform.pos.y);
				rect.setFillColor(sf::Color(0, 0, 0, 0));
				rect.setOutlineColor(sf::Color(255, 255, 255, 255));
				rect.setOutlineThickness(1);
				m_game->window().draw(rect);
			}
		}
	}

	//draw the grid for easy debug
	if (m_drawGrid)
	{
		float leftX = m_game->window().getView().getCenter().x - width() / 2;
		float rightX = leftX + width() + m_gridSize.x;
		float nextGridX = leftX - ((int)leftX % (int)m_gridSize.x);

		for (float x = nextGridX; x < rightX; x += m_gridSize.x)
		{
			drawLine(Vec2(x, 0), Vec2(x, height()));
		}

		for (float y = 0; y < height(); y += m_gridSize.y)
		{
			drawLine(Vec2(leftX, height() - y), Vec2(rightX, height() - y));

			for (float x = nextGridX; x < rightX; x += m_gridSize.x)
			{
				std::string xCell = std::to_string((int)x / (int)m_gridSize.x);
				std::string yCell = std::to_string((int)y / (int)m_gridSize.y);
				gridText.setString("(" + xCell + "," + yCell + ")");
				gridText.setPosition({ x + 3, height() - y - m_gridSize.y + 2 });
				m_game->window().draw(gridText);
			}
		}

	}
}

void Scene_Platformer::sEnemySpawner()
{

}

void Scene_Platformer::sDebug()
{

}
