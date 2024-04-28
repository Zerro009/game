#pragma once

#include "State.h"
#include "gui.h"

class OnlineMenuState : public State {
private:
	sf::Font font;
	std::map<std::string, gui::Button*> buttons;
	std::map<std::string, gui::InputField*> inputFields;

	// Inits
	void			initVariables();
	void			initKeybinds();
	void			initFonts();
	void			initGui();
public:
	OnlineMenuState(StateData *stateData);
	virtual ~OnlineMenuState();

	// Updates
	void			updateInput(const float dt);
	void			updateButtons();
	void			updateInputs();
	void			updateGui();

	// Renders
	void			renderButtons(sf::RenderTarget* target = NULL);
	void			renderInputs(sf::RenderTarget* target = NULL);
	void			renderGui(sf::RenderTarget* target = NULL);

	// Core
	void			update(const float dt);
	void			render(sf::RenderTarget *target = NULL);
};

