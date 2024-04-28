#include "gui.h"

using namespace gui;

Button::Button(float x, float y, float width, float height,
	sf::Font* font, std::string text,
	sf::Color textColor, sf::Color textHoverColor, sf::Color textActiveColor,
	sf::Color color, sf::Color hoverColor, sf::Color activeColor,
	sf::Color borderColor, sf::Color borderHoverColor, sf::Color borderActiveColor,
	short unsigned id) {

	this->btnState = BTN_IDLE;
	this->id = id;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(color);
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(borderColor);

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(textColor);
	this->text.setCharacterSize(14);

	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y
	);

	this->textColor = textColor;
	this->textHoverColor = textHoverColor;
	this->textActiveColor = textActiveColor;

	this->color = color;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;

	this->borderColor = borderColor;
	this->borderHoverColor = borderHoverColor;
	this->borderActiveColor = borderActiveColor;
}

Button::~Button() {
}

// Button Accessors
const bool gui::Button::isPressed() const
{
	if (this->btnState == BTN_ACTIVE)
		return true;

	return false;
}

const std::string gui::Button::getText() const
{
	return this->text.getString();
}

const short unsigned& gui::Button::getId() const
{
	return this->id;
}

// Button Modifiers
void gui::Button::setText(const std::string text)
{
	this->text.setString(text);
}

void gui::Button::setId(const short unsigned id)
{
	this->id = id;
}

// Button Core
void Button::update(const sf::Vector2i mousePosWindow) {
	//Idle
	this->btnState = BTN_IDLE;

	//Hover
	if (this->shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
	{
		this->btnState = BTN_HOVER;

		//Pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->btnState = BTN_ACTIVE;
		}
	}

	switch (this->btnState)
	{
	case BTN_IDLE:
		this->shape.setFillColor(this->color);
		this->text.setFillColor(this->textColor);
		this->shape.setOutlineColor(this->borderColor);
		break;

	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		this->text.setFillColor(this->textHoverColor);
		this->shape.setOutlineColor(this->borderHoverColor);
		break;

	case BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		this->text.setFillColor(this->textActiveColor);
		this->shape.setOutlineColor(this->borderActiveColor);
		break;

	default:
		this->shape.setFillColor(sf::Color::Red);
		this->text.setFillColor(sf::Color::Blue);
		this->shape.setOutlineColor(sf::Color::Green);
		break;
	}
}

void Button::render(sf::RenderTarget* target) {
	target->draw(this->shape);
	target->draw(this->text);
}