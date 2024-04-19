#include "stdafx.h"
#include "GUI.h"

const float GUI::PixelPercentX(const float perc, const sf::VideoMode& vm)
{
	return std::floor(vm.width * (perc / 100.f));
}

const float GUI::PixelPercentY(const float perc, const sf::VideoMode& vm)
{
	return std::floor(vm.height * (perc / 100.f));
}

const unsigned GUI::calcCharSize(const sf::VideoMode& vm)
{
	return static_cast<unsigned>((vm.width + vm.height) / 60);
}


//button

GUI::Button::Button(float x, float y, float width, float height, std::wstring text, sf::Color textColor, sf::Font* font,
	sf::Color idle, sf::Color hover, sf::Color pressed, unsigned charSize, sf::Color idleColor, sf::Color hoverColor, sf::Color pressedColor, sf::Color outline, short unsigned id)
{
	this->buttonShape.setPosition(sf::Vector2f(x, y));
	this->buttonShape.setSize(sf::Vector2f(width, height));
	this->buttonShape.setOutlineColor(outline);
	this->buttonShape.setOutlineThickness(1);
	this->font = font;
	this->Buttontext.setFont(*this->font);
	this->Buttontext.setString(text);
	this->Buttontext.setFillColor(textIdle);
	this->Buttontext.setCharacterSize(charSize);
	this->idle = idle;
	this->hover = hover;
	this->pressed = pressed;
	this->buttonShape.setFillColor(idle);
	this->Buttontext.setPosition(
		this->buttonShape.getPosition().x + (this->buttonShape.getGlobalBounds().width / 2.f) - this->Buttontext.getGlobalBounds().width / 2.f,
		this->buttonShape.getPosition().y + (this->buttonShape.getGlobalBounds().height / 2.f) - this->Buttontext.getGlobalBounds().height / 1.2f);

	this->textIdle = idleColor;
	this->textHover = hoverColor;
	this->textPressed = pressedColor;
	this->buttonState = idle_state;
	this->lastState = idle_state;
	this->setId(id);

}

GUI::Button::~Button()
{

}

void GUI::Button::update(const sf::Vector2i& mousePosition)
{
	this->buttonState = idle_state;
	if (this->buttonShape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)))
	{
		this->buttonState = hover_state;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->lastState != pressed_state)
		{
			this->lastState = pressed_state;
		}

		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->lastState == pressed_state)
		{
			this->buttonState = pressed_state;
			this->lastState = idle_state;
		}
	}

	switch (this->buttonState)
	{
	case idle_state:
		this->buttonShape.setFillColor(this->idle);
		this->Buttontext.setFillColor(this->textIdle);
		break;
	case hover_state:
		this->buttonShape.setFillColor(this->hover);
		this->Buttontext.setFillColor(this->textHover);
		break;
	case pressed_state:
		this->buttonShape.setFillColor(this->pressed);
		this->Buttontext.setFillColor(this->textPressed);
		break;
	default:
		this->buttonShape.setFillColor(sf::Color::Red);
		break;
	}
		
}

void GUI::Button::render(sf::RenderTarget& target)
{
	target.draw(this->buttonShape);
	target.draw(this->Buttontext);
}

const bool GUI::Button::isPressed() const
{
	if (this->buttonState == pressed_state)
		return true;


	return false;
}

const std::wstring GUI::Button::getText() const 
{
	return this->Buttontext.getString() ;
}

void GUI::Button::setText(const std::wstring text)
{
	this->Buttontext.setString((L"%d", text));
}

const short unsigned& GUI::Button::getId() const
{
	return this->id;
}

void GUI::Button::setId(const short unsigned id)
{
	this->id = id;
}

void GUI::Button::updateProperties(const float x, const float y, const float width, const float height, short unsigned charSize)
{
	this->buttonShape.setSize(sf::Vector2f(width, height));
	this->buttonShape.setPosition(sf::Vector2f(x, y));
	this->Buttontext.setCharacterSize(charSize);
	this->Buttontext.setPosition(
		this->buttonShape.getPosition().x + (this->buttonShape.getGlobalBounds().width / 2.f) - this->Buttontext.getGlobalBounds().width / 2.f,
		this->buttonShape.getPosition().y + (this->buttonShape.getGlobalBounds().height / 2.f) - this->Buttontext.getGlobalBounds().height / 1.2f);
}
//drop down

GUI::DropDownList::DropDownList(float x, float y, float width, float height, sf::Font& font, unsigned charsize, std::wstring list[], unsigned numOfElems, unsigned defaultIndex) 
	: font(font), showList(false), numOfElems(numOfElems)
{

	this->activeElem = new Button(x, y, width, height,
		list[defaultIndex], sf::Color(52, 61, 70, 0), &this->font,
		sf::Color(107, 36, 12, 150),
		sf::Color(245, 204, 160, 150),
		sf::Color(52, 61, 70, 150),
		charsize,
		sf::Color(255, 255, 255, 255),
		sf::Color(255, 255, 255, 255),
		sf::Color(255, 255, 255, 255), sf::Color::Black, 0);

	for (size_t i = 1; i < numOfElems; i++)
	{
		this->list.push_back(new Button(x, y + (i * height), width, height,
			list[i], sf::Color(52, 61, 70, 0), &this->font,
			sf::Color(107, 36, 12, 150),
			sf::Color(245, 204, 160, 150),
			sf::Color(52, 61, 70, 150),
			charsize,
			sf::Color(255, 255, 255, 255),
			sf::Color(255, 255, 255, 255),
			sf::Color(255, 255, 255, 255), sf::Color::Transparent, i));
	}

}

GUI::DropDownList::~DropDownList()
{
	delete this->activeElem;

	for (size_t i = 0; i < this->numOfElems - 1; i++)
	{
		delete this->list[i];
	}
}

const unsigned short& GUI::DropDownList::getActiveElemID() const
{
	return this->activeElem->getId();
}

void GUI::DropDownList::update(const sf::Vector2i& mousePosition, const float& dt)
{
	this->activeElem->update(mousePosition);

	if (this->showList)
	{
		for (auto& i : this->list)
		{
			i->update(mousePosition);
		}
	}
}

void GUI::DropDownList::render(sf::RenderTarget& target)
{
	this->activeElem->render(target);

	if (this->activeElem->isPressed())
	{
		if (this->showList)
			this->showList = false;
		else
			this->showList = true;
	}

	if (this->showList)
	{
		for (auto& i : list)
		{
			i->render(target);

			if (i->isPressed())
			{	
				if (i->getId() != this->activeElem->getId())
				{
					this->showList = 0;
				}
				this->activeElem->setId(i->getId());
			}

		}
	}
}

GUI::TextureSelector::TextureSelector(float x, float y, float width, float height, float gridsize, const sf::Texture* texture) : gridsize(gridsize), active(0), hidden(0)
{
	this->bounds.setSize(sf::Vector2f(width, height));
	this->bounds.setPosition(x, y);
	this->bounds.setFillColor(sf::Color(255, 255, 255, 50));
	this->bounds.setOutlineColor(sf::Color(255, 255, 255, 200));	
	this->bounds.setOutlineThickness(1.f);

	this->sheet.setTexture(*texture);
	this->sheet.setPosition(x, y);

	if (this->sheet.getGlobalBounds().width > this->bounds.getGlobalBounds().width)
	{
		this->sheet.setTextureRect(sf::IntRect(0, 0, this->sheet.getGlobalBounds().width, this->sheet.getGlobalBounds().height));
	}
	if (this->sheet.getGlobalBounds().height > this->bounds.getGlobalBounds().height)
	{
		this->sheet.setTextureRect(sf::IntRect(0, 0, this->sheet.getGlobalBounds().height, this->sheet.getGlobalBounds().width));	
	}

	this->selector.setPosition(x, y);
	this->selector.setSize(sf::Vector2f(this->gridsize, this->gridsize));
	this->selector.setFillColor(sf::Color::Transparent);
	this->selector.setOutlineThickness(1.f);
	this->selector.setOutlineColor(sf::Color::Red);

	this->textureRect.width = static_cast<int>(this->gridsize);
	this->textureRect.height = static_cast<int>(this->gridsize);

}

GUI::TextureSelector::~TextureSelector()
{

}

void GUI::TextureSelector::update(const sf::Vector2i& mousepos)
{

	if (!this->hidden)
	{
			if (this->bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousepos)))
				this->active = 1;
			else
				this->active = 0;

			if (this->active)
			{
				this->mousePosGrid.x = ((mousepos.x - static_cast<int>(this->bounds.getPosition().x)) / static_cast<unsigned>(this->gridsize));
				this->mousePosGrid.y = ((mousepos.y - static_cast<int>(this->bounds.getPosition().y)) / static_cast<unsigned>(this->gridsize));

				this->selector.setPosition(this->bounds.getPosition().x + this->mousePosGrid.x * this->gridsize, this->bounds.getPosition().y + this->mousePosGrid.y * this->gridsize);

				this->textureRect.left = static_cast<int>(this->selector.getPosition().x - this->bounds.getPosition().x);
				this->textureRect.top = static_cast<int>(this->selector.getPosition().y - this->bounds.getPosition().y);
				this->textureRect.width = static_cast<int>(this->gridsize);
				this->textureRect.height = static_cast<int>(this->gridsize);
			}
	}
}

void GUI::TextureSelector::render(sf::RenderTarget& target)
{


	if (!this->hidden)
	{
		target.draw(this->bounds);
		target.draw(this->sheet);
		if (this->active)
			target.draw(this->selector);
	}
}	

bool& GUI::TextureSelector::getActive()
{
	return this->active;
}

const sf::IntRect& GUI::TextureSelector::getTextureRect() const
{
	return this->textureRect;
}


// progress bar
GUI::ProgressBar::ProgressBar(float x, float y, float width, float height, int maxValue, sf::Color* color, sf::Font* font, sf::VideoMode* vm)
{
	this->color = *color;
	this->vm = *vm;
	this->maxValue = maxValue;
	this->barMaxWidth = width;

	this->back.setSize(sf::Vector2f(width, height));
	this->back.setFillColor(sf::Color(0, 0, 0, 50));
	this->back.setPosition(x, y);
	this->back.setOutlineThickness(1.f);
	this->back.setOutlineColor(sf::Color(255, 255, 255, 200));

	this->front.setSize(sf::Vector2f(width, height));
	this->front.setFillColor(sf::Color(this->color));
	this->front.setPosition(this->back.getPosition());

	if (font)
	{
		this->font = *font;
		this->text.setFont(this->font);
		this->text.setCharacterSize(GUI::calcCharSize(*vm) - 10);
	}

}

GUI::ProgressBar::~ProgressBar()
{

}

void GUI::ProgressBar::update(const int currentValue)
{
	float percent = static_cast<float>(currentValue) / static_cast<float>(this->maxValue);

	this->front.setSize(sf::Vector2f(static_cast<float>(std::floor(this->barMaxWidth * percent)), this->front.getSize().y));

	this->barStr = std::to_string(currentValue) + " / " + std::to_string(maxValue);
	this->text.setString(barStr);
	this->text.setPosition(this->back.getPosition().x + (this->back.getSize().x / 2 - this->text.getGlobalBounds().width / 2),
		this->back.getPosition().y + (this->back.getSize().y / 2 - this->text.getGlobalBounds().height / 1.5));
}

void GUI::ProgressBar::render(sf::RenderTarget& target)
{
	target.draw(this->back);
	target.draw(this->front);
	target.draw(this->text);
}
