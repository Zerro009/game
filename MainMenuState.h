#pragma once

#include "gui.h"
#include "GameState.h"

class MainMenuState : public State {
private:
	sf::Font font;
	std::map<std::string, gui::Button*> buttons;

	// Inits
	void			initVariables();
	void			initKeybinds();
	void			initFonts();
	void			initGui();
public:
	MainMenuState(StateData* stateData);
	virtual ~MainMenuState();

	// Updates
	void			updateInput(const float dt);
	void			updateButtons();

	// Renders
	void			renderButtons(sf::RenderTarget *target = NULL);

	// Core
	void			update(const float dt);
	void			render(sf::RenderTarget *target = NULL);
};

