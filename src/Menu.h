#pragma once

#include "gui.h"

class Menu {
private:
	sf::Font	*font;
	gui::Frame	*frame;

	// Inits
public:
	Menu(sf::VideoMode *vm, sf::Font *font);
	virtual ~Menu();

	// Core
	void			update(const sf::Vector2i mousePosWindow);
	void			render(sf::RenderTarget *target);
};
