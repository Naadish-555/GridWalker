#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameEngine.hpp"
#include "Vec2.hpp"


int main()
{
	GameEngine g(RESOURCES_PATH "assets.txt");
	g.run();
	std::cout << "Output on console" << std::endl;

	std::cout << std::endl << "=====================================================================================";

	ImGui::SFML::Shutdown();



	return 0;
}