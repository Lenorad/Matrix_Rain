#pragma once

#include "Matrix_Drop.h"
constexpr auto RAIN_DROPS = 45;

class Application {
public:
	Application();
	~Application();
	void run();
private:
	void processEvents();
	void update(sf::Time);
	void render();
private:
	sf::RenderWindow mWindow;
	sf::Font font;
};
