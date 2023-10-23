#pragma once

#include <SFML\Graphics.hpp>

#include <stdlib.h>
#include <time.h>
#include <string>

constexpr auto CharacterSizeMin = 10;
constexpr auto CharacterSizeMax = 25;
constexpr auto WindowWidth = 1920;
constexpr auto WindowHeight = 1080;
constexpr auto RandomStringLengthMin = 5;
constexpr auto RandomStringLengthMax = 25;
constexpr auto UpdateSpeedMin = 5;
constexpr auto UpdateSpeedMax = 25;

struct Matrix_Text {

	// The followings get initialized on Constructor
	unsigned int characterSize;
	sf::Vector2f position;
	float update_speed;
	std::string str;

	Matrix_Text();
};

void generate_string(std::string&, int);
float generate_position(int);
int rrandom(int, int);