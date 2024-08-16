#pragma once

#include "pch.h"

class Graphics {
public:
	Graphics();
	virtual ~Graphics();

	std::string					title;
	sf::VideoMode				resolution;
	bool						fullscreen;
	bool						vSync;
	unsigned					framerateLimit;
	sf::ContextSettings			contextSettings;
	std::vector<sf::VideoMode>	videoModes;

	// Funcs
	void						saveToFile(const std::string path);
	void						loadFromFile(const std::string path);
};

