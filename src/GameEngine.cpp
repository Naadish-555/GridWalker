#include "GameEngine.hpp"
//include scene specific files

#include <fstream>
#include <iostream>
#include <Scene_GE_Menu.h>

GameEngine::GameEngine(const std::string& path)
{
	init(path);
}

void GameEngine::init(const std::string& path)
{
	Assets::Instance().loadFromFile(path);

	std::cout << "Total textuers loaded: " << Assets::Instance().getTextures().size() << "\n";
	std::cout << "Total animations loaded: " << Assets::Instance().getAnimations().size() << "\n";

	std::ifstream fin(RESOURCES_PATH "config.txt");
	std::string input;
	int wWidth = 0, wHeight = 0;

	while (fin.good())
	{
		fin >> input;
		std::cout << "Token Read: [" << input << "]" << std::endl;
		if (input[0] == '#')
		{
			std::string dummy;
			std::getline(fin, dummy);
			continue; 
		}
		
		else if (input == "Window" || input == "window")
		{
			fin >> m_windowConfig.WW >> m_windowConfig.WH >> m_windowConfig.R >> m_windowConfig.G >> m_windowConfig.B >> m_windowConfig.FL >> m_windowConfig.FS  ;
		}

		else
		{
			std::cout << "invalid input :" << input << std::endl;
		}
		
		
	}

	//set up default window parameters
	if (m_windowConfig.FS == 1)
	{
		m_window.create(sf::VideoMode(m_window.getSize().x, m_window.getSize().y), "Platformer", sf::Style::Fullscreen);
	}
	else
	{
		m_window.create(sf::VideoMode(m_windowConfig.WW, m_windowConfig.WH), "Platformer");
	}

	m_window.setFramerateLimit(m_windowConfig.FL);
	m_window.setKeyRepeatEnabled(false);

	//ImGUI setup

	if (!ImGui::SFML::Init(m_window)) {};
	//you can use whatever imgui theme you like!
	//ImGui::StyleColorsDark();				
	//imguiThemes::yellow();
	//imguiThemes::gray();
	//imguiThemes::green();
	//imguiThemes::red();
	//imguiThemes::gray();

	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	io.FontGlobalScale = 1.5f;
	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_WindowBg].w = 0.95f;
	//style.Colors[ImGuiCol_DockingEmptyBg].w = 0.f;

	changeScene("MENU", std::make_shared<Scene_GE_Menu>(this));

}

void GameEngine::run()
{
	while (isRunning())
	{
		//calculate the delta time
		sf::Time deltaTime = m_deltaClock.restart();
		float deltaTimeSeconds = deltaTime.asSeconds();


		//make sure delta time stays within normal bounds, like between one FPS and zero FPS
		deltaTimeSeconds = std::min(deltaTimeSeconds, 1.f);
		deltaTimeSeconds = std::max(deltaTimeSeconds, 0.f);


		m_dt = deltaTimeSeconds;
		if (m_dt > 0.0f)
		{
			m_fps = 1.0f / m_dt;
		}

		ImGui::SFML::Update(m_window, deltaTime);
		update();
		ImGui::EndFrame();
	}
	ImGui::SFML::Shutdown();
}

void GameEngine::sUserInput()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		ImGui::SFML::ProcessEvent(m_window, event);

		if (event.type == sf::Event::Closed)
		{
			quit();
		}

		if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
		{
			if (currentScene()->getActionMap().find(event.key.code) == currentScene()->getActionMap().end())
			{
				continue;
			}

			const std::string actionType = (event.type == sf::Event::KeyPressed) ? "START" : "END";

			currentScene()->doAction(Action(currentScene()->getActionMap().at(event.key.code), actionType));
		}

		auto mousePos = sf::Mouse::getPosition(m_window);
		Vec2 pos((float)mousePos.x, (float)mousePos.y);
		if (event.type == sf::Event::MouseButtonPressed)
		{
			switch (event.mouseButton.button)
			{
			case sf::Mouse::Left:
			{
				currentScene()->doAction(Action("LEFT_CLICK", "START", pos));
				break;
			}
			case sf::Mouse::Middle:
			{
				currentScene()->doAction(Action("MIDDLE_CLICK", "START", pos));
				break;
			}
			case sf::Mouse::Right:
			{
				currentScene()->doAction(Action("RIGHT_CLICK", "START", pos));
				break;
			}
			default:
				break;
			}

			if (event.type == sf::Event::MouseButtonReleased)
			{
				switch (event.mouseButton.button)
				{
				case sf::Mouse::Left:
				{
					currentScene()->doAction(Action("LEFT_CLICK", "END", pos));
					break;
				}
				case sf::Mouse::Middle:
				{
					currentScene()->doAction(Action("MIDDLE_CLICK", "END", pos));
					break;
				}
				case sf::Mouse::Right:
				{
					currentScene()->doAction(Action("RIGHT_CLICK", "END", pos));
					break;
				}
				default:
					break;
				}

				if (event.type == sf::Event::MouseMoved)
				{
					currentScene()->doAction(Action("MOUSE_MOVE", Vec2((float)event.mouseMove.x, (float)event.mouseMove.y)));
				}
			}
		}
	}
}

void GameEngine::changeScene(const std::string& sceneName, std::shared_ptr<Scene> scene, bool endCurrentScene)
{
	if (scene)
	{
		m_SceneMap[sceneName] = scene;
	}
	else
	{
		if (m_SceneMap.find(sceneName) == m_SceneMap.end())
		{
			std::cerr << "Warning : scene does not exist" << sceneName << std::endl;
			return;
		}
	}

	if (endCurrentScene)
	{
		m_SceneMap.erase(m_SceneMap.find(m_currentScene));
	}
	m_currentScene = sceneName;
}

void GameEngine::update()
{
	if (!isRunning() || m_SceneMap.empty()) { return; }

	sUserInput();
	currentScene()->simulate(m_simulationSpeed);

	//Render system is seperated form scene update so the game engine can simulate a
	// specified number of frames without rendeing each frame of simulation
	currentScene()->sRender();
	ImGui::SFML::Render(m_window);
	m_window.display();
}

	

