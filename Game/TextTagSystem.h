#pragma once


class TextTag;

class TextTagSystem
{
private:
	class TextTag {
	public:

	};


public:
	TextTagSystem();
	virtual ~TextTagSystem();

	void update(const float& dt);
	void render(sf::RenderTarget* target);

	void addText(TextTag* textTag);
	void removeTextTag();

};

