#include "Menu.h"

Menu::Menu(sf::VideoMode *vm, sf::Font *font) : font(font) {
	this->frame = new gui::Frame(
			20.f, 60.f,
			200.f, 400.f,
			"Menu",
			sf::Color::Red,
			sf::Color(32, 32, 32)
	);
}

Menu::~Menu() {
	delete this->frame;
}

// Core
void Menu::update(const sf::Vector2i mousePosWindow) {
	this->frame->update(mousePosWindow);
}

void Menu::render(sf::RenderTarget *target) {
	this->frame->render(target);
}
