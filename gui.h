#pragma once

#include "pch.h"

enum btn_states {
	BTN_IDLE = 0x0,
	BTN_HOVER,
	BTN_ACTIVE,
};

namespace gui {
	class Button {
	private:
		short unsigned btnState;
		short unsigned id;

		sf::RectangleShape shape;
		sf::Font* font;
		sf::Text text;

		sf::Color textColor;
		sf::Color textHoverColor;
		sf::Color textActiveColor;

		sf::Color color;
		sf::Color hoverColor;
		sf::Color activeColor;

		sf::Color borderColor;
		sf::Color borderHoverColor;
		sf::Color borderActiveColor;
	public:
		Button(float x, float y, float width, float height,
			sf::Font* font, std::string text,
			sf::Color textColor, sf::Color textHoverColor, sf::Color textActiveColor,
			sf::Color color, sf::Color hoverColor, sf::Color activeColor,
			sf::Color borderColor, sf::Color borderHoverColor, sf::Color borderActiveColor,
			short unsigned id = 0);
		~Button();

		//Accessors
		const bool isPressed() const;
		const std::string getText() const;
		const short unsigned& getId() const;

		//Modifiers
		void		setText(const std::string text);
		void		setId(const short unsigned id);

		// Core
		void		update(const sf::Vector2i mousePosWindow);
		void		render(sf::RenderTarget* target);
	};
};

