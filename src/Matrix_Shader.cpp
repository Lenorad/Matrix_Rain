#include "matrix_shader.h"
#define SIZE round(textBounds.height * portion) * 2

Matrix_Shader::Matrix_Shader(const sf::FloatRect& tB, const sf::Vector2f& tO, const float& por, const float& sp) :
	textBounds(tB), textOffset(tO), portion(por), speed(sp)
{
	// Gradient Buffer
	Gradient.create(SIZE);
	Gradient.setPrimitiveType(sf::Lines);
	Gradient.setUsage(sf::VertexBuffer::Stream);

	verticesToBeDisplayed = SIZE;
	UoL = true;

	// Dynamic vertix arrays
	Vertices = new sf::Vertex[SIZE]{};

	generate_gradient();
	Gradient.update(Vertices);
}

Matrix_Shader::~Matrix_Shader()
{
	delete[] Vertices_offset;
	delete[] Vertices;
}

void Matrix_Shader::update(const float seconds)
{
	moveDown_gradient(seconds);
	generate_transparent();
	if (UoL)
		Gradient.update(Vertices_offset);
	else
		Gradient.update(Vertices, verticesToBeDisplayed, 0);
}

sf::VertexBuffer Matrix_Shader::getGradient() { return Gradient; }
sf::VertexArray Matrix_Shader::getUpper() { return upperTransparent; };
sf::VertexArray Matrix_Shader::getLower() { return lowerTransparent; };

void Matrix_Shader::generate_gradient()
{
	const int t = ceil(textBounds.height * portion / 255);
	const float step = (255 * t) / (textBounds.height * portion);

	int y_increment = 1;
	float alpha = 255;
	int index = 0;

	for (int i = 0; i < floor(textBounds.height * portion / t); ++i)
	{
		for (int j = 0; j < t; ++j)
		{
			Vertices[index * 2] = sf::Vertex(sf::Vertex(sf::Vector2f(textOffset.x + textBounds.left, textOffset.y + y_increment + textBounds.top), sf::Color(0, 0, 0, alpha)));
			Vertices[index * 2 + 1] = sf::Vertex(sf::Vertex(sf::Vector2f(textOffset.x + textBounds.left + textBounds.width, textOffset.y + y_increment + textBounds.top), sf::Color(0, 0, 0, alpha)));
			y_increment++; index++;
		}
		alpha -= step;
	}
	for (int i = floor(textBounds.height * portion / t) * t; i < round(textBounds.height * portion); i++)
	{
		Vertices[index * 2] = sf::Vertex(sf::Vertex(sf::Vector2f(textOffset.x + textBounds.left, textOffset.y + y_increment + textBounds.top), sf::Color(0, 0, 0, alpha)));
		Vertices[index * 2 + 1] = sf::Vertex(sf::Vertex(sf::Vector2f(textOffset.x + textBounds.width + textBounds.left, textOffset.y + y_increment + textBounds.top), sf::Color(0, 0, 0, alpha)));
		y_increment++; index++;
	}

	for (int i = 0; i < SIZE; ++i)
	{
		Vertices[i].position.y -= (SIZE / 2);
	}
}

void Matrix_Shader::moveDown_gradient(const float deltaSeconds)
{
	if (Vertices[0].position.y >= textBounds.height + textBounds.top + textOffset.y)
	{
		Ended = true;
		if (SelfDestructWhenEnd)
			this->~Matrix_Shader();
		else
			for (int i = 0; i < SIZE; ++i)
				Vertices[i].position.y = round(Vertices[i].position.y) - round(textBounds.height + SIZE / 2);
	}
	else
		for (int i = 0; i < SIZE; ++i)
			Vertices[i].position.y += speed * deltaSeconds;


	const int y_offset = textBounds.top + textOffset.y;
	const int last = SIZE - 1;

	if (Vertices[last].position.y > textBounds.height + y_offset)
	{
		UoL = false;
		Gradient.create(SIZE);
		verticesToBeDisplayed = floor(SIZE) - int(Vertices[last].position.y - (textBounds.height + y_offset)) * 2;
	}
	else if (Vertices[0].position.y < y_offset)
	{
		UoL = true;

		int upper = (y_offset - round(Vertices[0].position.y)) * 2;
		int lower = SIZE - upper;
		Vertices_offset = new sf::Vertex[lower]{};

		for (int i = 0; i < lower; ++i)
			Vertices_offset[i] = sf::Vertex(Vertices[i + upper].position, Vertices[upper + i].color);

		Gradient.create(lower);
		verOffc = lower;
	}
	else
	{
		UoL = false;
		Gradient.create(SIZE);
		verticesToBeDisplayed = SIZE;
	}
}

void Matrix_Shader::generate_transparent()
{
	const int last = SIZE - 1;
	const int x1 = textBounds.left + textOffset.x;
	const int x2 = x1 + textBounds.width;
	const int max = verticesToBeDisplayed - 1;

	const sf::Color transparent = sf::Color(0, 0, 0, 255);

	if (int(Vertices[0].position.y) == textBounds.top + textOffset.y)
		for (int i = 0; i < 4; ++i)
		{
			upperTransparent[i] = sf::Vertex(sf::Vertex());
			lowerTransparent[i] = sf::Vertex(sf::Vertex());
		}

	if (UoL)
	{
		upperTransparent[0] = sf::Vertex(sf::Vertex());
		upperTransparent[1] = sf::Vertex(sf::Vertex());
		upperTransparent[2] = sf::Vertex(sf::Vertex());
		upperTransparent[3] = sf::Vertex(sf::Vertex());
	}
	else
	{
		upperTransparent[0] = sf::Vertex(sf::Vertex(sf::Vector2f(x1, textBounds.top + textOffset.y), transparent));
		upperTransparent[1] = sf::Vertex(sf::Vertex(sf::Vector2f(x2, textBounds.top + textOffset.y), transparent));
		upperTransparent[2] = sf::Vertex(sf::Vertex(sf::Vector2f(x2, Vertices[0].position.y), transparent));
		upperTransparent[3] = sf::Vertex(sf::Vertex(sf::Vector2f(x1, Vertices[0].position.y), transparent));
	}
	if (verticesToBeDisplayed == SIZE)
	{
		lowerTransparent[0] = sf::Vertex(sf::Vertex(sf::Vector2f(x1, Vertices[max].position.y), transparent));
		lowerTransparent[1] = sf::Vertex(sf::Vertex(sf::Vector2f(x2, Vertices[max].position.y), transparent));
		lowerTransparent[2] = sf::Vertex(sf::Vertex(sf::Vector2f(x2, textBounds.height + textBounds.top + textOffset.y), transparent));
		lowerTransparent[3] = sf::Vertex(sf::Vertex(sf::Vector2f(x1, textBounds.height + textBounds.top + textOffset.y), transparent));
	}
	else if (UoL && verOffc != 0)
	{
		lowerTransparent[0] = sf::Vertex(sf::Vertex(sf::Vector2f(x1, Vertices_offset[verOffc - 1].position.y), transparent));
		lowerTransparent[1] = sf::Vertex(sf::Vertex(sf::Vector2f(x2, Vertices_offset[verOffc - 1].position.y), transparent));
		lowerTransparent[2] = sf::Vertex(sf::Vertex(sf::Vector2f(x2, textBounds.height + textBounds.top + textOffset.y), transparent));
		lowerTransparent[3] = sf::Vertex(sf::Vertex(sf::Vector2f(x1, textBounds.height + textBounds.top + textOffset.y), transparent));
	}
	else if (verticesToBeDisplayed != SIZE)
	{
		lowerTransparent[0] = sf::Vertex(sf::Vertex());
		lowerTransparent[1] = sf::Vertex(sf::Vertex());
		lowerTransparent[2] = sf::Vertex(sf::Vertex());
		lowerTransparent[3] = sf::Vertex(sf::Vertex());
	}
	else
	{
		lowerTransparent[0] = sf::Vertex(sf::Vertex(sf::Vector2f(x1, textBounds.top + textOffset.y), transparent));
		lowerTransparent[1] = sf::Vertex(sf::Vertex(sf::Vector2f(x2, textBounds.top + textOffset.y), transparent));
		lowerTransparent[2] = sf::Vertex(sf::Vertex(sf::Vector2f(x2, textBounds.top + textOffset.y + textBounds.height), transparent));
		lowerTransparent[3] = sf::Vertex(sf::Vertex(sf::Vector2f(x1, textBounds.top + textOffset.y + textBounds.height), transparent));
	}
}