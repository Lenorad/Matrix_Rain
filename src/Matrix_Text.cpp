#include "Matrix_Text.h"

Matrix_Text::Matrix_Text()
{
	characterSize = rrandom(CharacterSizeMin, CharacterSizeMax);
	position = { generate_position(WindowWidth), generate_position(WindowHeight - 400) };
	generate_string(str, rrandom(RandomStringLengthMin, RandomStringLengthMax));
	update_speed = float(rrandom(UpdateSpeedMin, UpdateSpeedMax)) / 10;
}

void generate_string(std::string& inputString, int length)
{
	std::string randomchar;
	inputString.clear();
	for (int i = 0; i < length; ++i)
	{
		randomchar = char(rand() % 94 + 33);
		inputString.append(randomchar);
		inputString.append("\n");
	}
}

float generate_position(int max)
{
	return rand() % max;
}

int rrandom(int min, int max)
{
	return rand() % (max - min + 1) + min;
}