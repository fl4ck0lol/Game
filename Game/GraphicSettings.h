#pragma once
class GraphicSettings
{
public:
	GraphicSettings();

	std::string title;
	sf::VideoMode resolution;
	bool fullscreen;
	bool vsync;
	unsigned frameLimit;
	sf::ContextSettings contextSettings;
	std::vector<sf::VideoMode> vmodes;

	//funcs
	void saveFromFile(const std::string path);

	void loadFromFile(const std::string path);
};

