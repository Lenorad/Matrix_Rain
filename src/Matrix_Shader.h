#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>

#include <math.h>

class Matrix_Shader {
public:
	Matrix_Shader(const sf::FloatRect&, const sf::Vector2f&, const float&, const float&);
	~Matrix_Shader();

	void update(const float);
	sf::VertexBuffer getGradient();
	sf::VertexArray getUpper();
	sf::VertexArray getLower();

public:
	bool Ended = false;

private:
	void generate_gradient();
	void moveDown_gradient(const float);
	void generate_transparent();

private:
	bool UoL;
	int verOffc;
	float speed;
	float portion;
	size_t verticesToBeDisplayed;
	bool SelfDestructWhenEnd = false;

	sf::FloatRect textBounds;
	sf::Vector2f textOffset;
	sf::VertexBuffer Gradient;
	sf::Vertex* Vertices_offset;
	sf::Vertex* Vertices;
	sf::VertexArray upperTransparent = sf::VertexArray(sf::PrimitiveType::Quads, 4);
	sf::VertexArray lowerTransparent = sf::VertexArray(sf::PrimitiveType::Quads, 4);
};