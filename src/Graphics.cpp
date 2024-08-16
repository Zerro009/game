#include "Graphics.h"

Graphics::Graphics() {
	this->title = "DEFAULT";
	this->resolution = sf::VideoMode::getDesktopMode();
	this->fullscreen = false;
	this->vSync = false;
	this->framerateLimit = 120;
	this->contextSettings.antialiasingLevel = 0;
	this->videoModes = sf::VideoMode::getFullscreenModes();
}

Graphics::~Graphics() {
}

// Funcs
void Graphics::saveToFile(const std::string path) {
	std::ofstream ofs(path);

	if (ofs.is_open()) {
		ofs << this->title;
		ofs << this->resolution.width << " " << this->resolution.height;
		ofs << this->fullscreen;
		ofs << this->framerateLimit;
		ofs << this->vSync;
		ofs << this->contextSettings.antialiasingLevel;
	}

	ofs.close();
}

void Graphics::loadFromFile(const std::string path) {
	std::ifstream ifs(path);

	if (ifs.is_open()) {
		std::getline(ifs, this->title);
		ifs >> this->resolution.width >> this->resolution.height;
		ifs >> this->fullscreen;
		ifs >> this->framerateLimit;
		ifs >> this->vSync;
		ifs >> this->contextSettings.antialiasingLevel;
	}

	ifs.close();
}