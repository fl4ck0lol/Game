#pragma once



enum button_states{idle_state = 0, hover_state, pressed_state};

namespace GUI {

	class Button
	{

	private:
		sf::RectangleShape buttonShape;
		sf::Font* font;
		sf::Text Buttontext;

		sf::Color idle;
		sf::Color hover;
		sf::Color pressed;

		sf::Color textIdle;
		sf::Color textHover;
		sf::Color textPressed;

		sf::Color outline;

		short unsigned buttonState;
		short unsigned lastState;
		short unsigned id;

	public:
		Button(float x, float y, float width, float height, std::wstring text, sf::Color textColor,
			sf::Font* font, sf::Color idle, sf::Color hover, sf::Color pressed, unsigned charSize, sf::Color idleColor, sf::Color hoverColor, sf::Color pressedColor, sf::Color outline, short unsigned id = 0);
		~Button();

		void update(const sf::Vector2i& mousePosition);
		void render(sf::RenderTarget& target);

		const bool isPressed() const;
		const std::wstring getText() const;

		void setText(const std::wstring text);
		const short unsigned& getId() const;

		void setId(const short unsigned id);

		void updateProperties(const float x, const float y, const float width, const float height, short unsigned charSize);

	};

	class DropDownList {

	private:
		Button* activeElem;
		std::vector<Button*> list;
		sf::Font& font;
		bool showList;

		unsigned numOfElems;

	public:
		DropDownList(float x, float y, float width, float height, sf::Font& font, unsigned charsize, std::wstring list[], unsigned numOfElems, unsigned deauftIndex);
		virtual ~DropDownList();

		const unsigned short& getActiveElemID() const;

		void update(const sf::Vector2i& mousePosition, const float& dt);
		void render(sf::RenderTarget& target);
	};

	class TextureSelector
	{
	private:

		sf::RectangleShape bounds;
		sf::Sprite sheet;
		sf::RectangleShape selector;
		sf::Vector2u mousePosGrid;
		sf::IntRect textureRect;
		bool active;
		bool hidden;
		float gridsize;

	public:
		TextureSelector(float x, float y, float width, float height, float gridsize, const sf::Texture* texture );
		~TextureSelector();

		void update(const sf::Vector2i& mousepos);
		void render(sf::RenderTarget& target);

		bool& getActive();
		const sf::IntRect& getTextureRect() const;
	};
	const float PixelPercentX(const float perc, const sf::VideoMode& vm);
	const float PixelPercentY(const float perc, const sf::VideoMode& vm);
	const unsigned calcCharSize(const sf::VideoMode& vm);
}