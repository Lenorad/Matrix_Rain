#pragma once

#include "Matrix_Text.h"
#include "Matrix_Shader.h"

class Matrix_Drop{
	static uint16_t S_ids;
	static sf::Font S_Font;
	static sf::Color S_Color;
public:
	static Matrix_Drop* S_Array;
public:
	Matrix_Drop();
	~Matrix_Drop();

	static void setFontAndColor(const sf::Font&, const sf::Color&);
	static void remove(const uint16_t);
	static void assign(const uint16_t);

	void update(sf::Time);

	void setID(const uint16_t id);

	sf::Text getText();
	Matrix_Text getTextProps();
	Matrix_Shader* getShader();

private:
	void blink(const float);

private:
	uint16_t ID;
	Matrix_Text mTextProps;
	Matrix_Shader* mShader;
	sf::Text mText;

	sf::FloatRect bounds;
	float portion;
	float speed;
	float cpyUpSpeed;
};
