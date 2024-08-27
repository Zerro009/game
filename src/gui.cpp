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

// InputField
InputField::InputField(float x, float y, float width, float height,
	sf::Font* font, std::string text,
	sf::Color textColor, sf::Color textHoverColor, sf::Color textActiveColor,
	sf::Color color, sf::Color hoverColor, sf::Color activeColor,
	sf::Color borderColor, sf::Color borderHoverColor, sf::Color borderActiveColor,
	short unsigned id) {

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

InputField::~InputField() {
}

// InputField Accessors
const bool gui::InputField::isPressed() const
{
	if (this->state == INPUT_FIELD_ACTIVE)
		return true;

	return false;
}

const std::string gui::InputField::getText() const
{
	return this->text.getString();
}

const short unsigned& gui::InputField::getId() const
{
	return this->id;
}

// InputField Modifiers
void gui::InputField::setText(const std::string text)
{
	this->text.setString(text);
}

void gui::InputField::setId(const short unsigned id)
{
	this->id = id;
}

// InputField Core
void InputField::update(sf::Event *event) {
	if (event->type == sf::Event::TextEntered) {
		if (event->text.unicode == '\b') {
			// Удалить последний введенный символ
			if (!this->text.getString().isEmpty()) {
				this->text.setString(this->text.getString().substring(0, this->text.getString().getSize() - 1));
			}
		}
		else {
			// Добавить введенный символ в текстовое поле
			this->text.setString(this->text.getString() + event->text.unicode);
		}
	}
}

void InputField::render(sf::RenderTarget* target) {
	target->draw(this->shape);
	target->draw(this->text);
}

// ProgressBar
ProgressBar::ProgressBar(float x, float y, float width, float height,
				float current, float max, std::string text,
				sf::Color border, sf::Color color, sf::Color background) {
	this->current = current;
	this->max = max;

	float fraction = current / max;

	this->bar.setPosition(
		sf::Vector2f(
			x + 1,
			y + 1
		)
	);
	this->bar.setSize(
		sf::Vector2f(
			width * fraction - 2,
			height - 2
		)
	);
	this->bar.setFillColor(color);

	this->background.setPosition(
		sf::Vector2f(
			x,
			y
		)
	);
	this->background.setSize(
		sf::Vector2f(
			width,
			height
		)
	);
	this->background.setFillColor(background);
	this->background.setOutlineThickness(-1.f);
	this->background.setOutlineColor(border);
}

ProgressBar::~ProgressBar() {
}

// Core
void ProgressBar::update() {
}

void ProgressBar::render(sf::RenderTarget *target) {
	target->draw(background);
	target->draw(bar);
}

// Frame
Frame::Frame(float x, float y, float width, float height, std::string title,
		sf::Color border, sf::Color background) : title(title), border(border), background(background) {

	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setOutlineThickness(-1.f);
	this->shape.setOutlineColor(border);
	this->shape.setFillColor(background);
}

Frame::~Frame() {
}

void Frame::update(sf::Vector2i mousePosWindow) {

}

void Frame::render(sf::RenderTarget *target) {
	target->draw(this->shape);
}
