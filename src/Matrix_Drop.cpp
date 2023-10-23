#include "Matrix_Drop.h"

sf::Font Matrix_Drop::S_Font;
sf::Color Matrix_Drop::S_Color;
uint16_t Matrix_Drop::S_ids = 0;
Matrix_Drop* Matrix_Drop::S_Array;

Matrix_Drop::Matrix_Drop()
{
	setID(S_ids);
	S_ids++;

	mText.setString(mTextProps.str);
	mText.setPosition(mTextProps.position);
	mText.setCharacterSize(mTextProps.characterSize);

	mText.setFont(S_Font);
	mText.setFillColor(S_Color);

	portion = float(rrandom(30, 65)) / 100;
	speed = rrandom(70, 140);

	bounds = mText.getLocalBounds();
	cpyUpSpeed = mTextProps.update_speed;

	mShader = new Matrix_Shader[1]{ {bounds, mTextProps.position, portion, speed} };
}

Matrix_Drop::~Matrix_Drop()
{
	//delete mShader;
}

void Matrix_Drop::setFontAndColor(const sf::Font& f, const sf::Color& c) { S_Font = f; S_Color = c; }

void Matrix_Drop::remove(const uint16_t id) 
{
	S_Array[id].~Matrix_Drop();
	S_Array[id] = Matrix_Drop();
	S_Array[id].setID(id);
}

void Matrix_Drop::assign(const uint16_t size)
{	
	S_Array = new Matrix_Drop[size]{};
}

sf::Text Matrix_Drop::getText() { return mText; }
Matrix_Shader* Matrix_Drop::getShader() { return mShader; }
Matrix_Text Matrix_Drop::getTextProps() { return mTextProps; }

void Matrix_Drop::update(sf::Time deltaTime)
{
	if (!mShader->Ended)
		mShader->update(deltaTime.asSeconds());
	if (mShader->Ended)
	{
		this->~Matrix_Drop();
		this->remove(ID);
	}
}

void Matrix_Drop::setID(const uint16_t id) { ID = id; }

void Matrix_Drop::blink(const float seconds)
{
	mTextProps.update_speed -= seconds;
	if (mTextProps.update_speed <= 0)
	{
		mTextProps.update_speed = cpyUpSpeed;
		generate_string(mTextProps.str, mTextProps.str.size() / 2);
		mText.setString(mTextProps.str);
	}
}