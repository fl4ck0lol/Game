#include "stdafx.h"
#include "State.h"


State::State(StateData* stateData)
{
	this->stateData = stateData;
	this->window = stateData->window;
	this->supportedKeys = stateData->supportedKeys;
	this->quit = false;
	this->states = stateData->states;
	this->paused = false;
	this->gridSize = stateData->gridSize;
}


State::~State()
{

}

const bool& State::getQuit() const
{
	return this->quit;
}

void State::updateMousePositions(sf::View* view)
{
	this->mousePositionScreen = sf::Mouse::getPosition();
	this->mousePositionWindow = sf::Mouse::getPosition(*this->window);

	if(view)
		this->window->setView(*view);

	this->mousePositionView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
	this->mousePositionGrid = sf::Vector2i(
		static_cast<int>(this->mousePositionView.x) / static_cast<int>(this->gridSize),
		static_cast<int>(this->mousePositionView.y) / static_cast<int>(this->gridSize)
	);

	this->window->setView(this->window->getDefaultView());
}

void State::endState()
{
	this->quit = true;
}

void State::pauseState()
{
	this->paused = true;
}

void State::unpauseState()
{
	this->paused = false;
}

