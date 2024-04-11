#include "stdafx.h"
#include "graphicSettings.h"

GraphicSettings::GraphicSettings()
{
	this->title = "default";
	this->resolution = sf::VideoMode::getDesktopMode();
	this->fullscreen = false;
	this->vsync = false;
	this->frameLimit = 165;
	this->contextSettings.antialiasingLevel = 0;
	this->vmodes = sf::VideoMode::getFullscreenModes();
}

void GraphicSettings::saveFromFile(const std::string path)
{
	std::ofstream ofs(path);
	unsigned antialiasing = 0;
	if (ofs.is_open())
	{
		ofs << this->title;
		ofs << this->resolution.width << " " << this->resolution.height;
		ofs << this->fullscreen;
		ofs << this->frameLimit;
		ofs << this->vsync;
		ofs << this->contextSettings.antialiasingLevel;
	}
	ofs.close();
}

void GraphicSettings::loadFromFile(const std::string path)
{
	std::ifstream inFileStream(path);
	unsigned antialiasing = 0;
	if (inFileStream.is_open())
	{
		std::getline(inFileStream, this->title);
		inFileStream >> this->resolution.width >> this->resolution.height;
		inFileStream >> this->fullscreen;
		inFileStream >> this->frameLimit;
		inFileStream >> this->vsync;
		inFileStream >> this->contextSettings.antialiasingLevel;
	}
	inFileStream.close();
}
