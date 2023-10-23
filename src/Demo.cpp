//#include "matrix_shader.h"
//
//int main()
//{
//	sf::RenderWindow window(sf::VideoMode(640, 480), "Matrix");
//
//	sf::Font font;
//	sf::Text text;
//
//	font.loadFromFile("Arkitech Light.ttf");
//	text.setString("a\nl\nd\nk\n;\nf\nj\na\nk\nl\nd\nn\nj\n;");
//	text.setFont(font);
//	text.setFillColor(sf::Color::Green);
//	text.setPosition({ 300, 10 });
//
//	sf::FloatRect fr = text.getLocalBounds();
//	sf::Vector2f po = { 300, 10 };
//	const float pr = 0.6;
//	const float sp = 95;
//
//	Matrix_Shader shade(fr, po, pr, sp);
//
//	sf::Clock clock;
//	float up;
//	float seconds;
//	while (window.isOpen())
//	{
//		sf::Event event;
//		sf::Time deltaTime = clock.restart();
//		seconds = deltaTime.asSeconds();
//		while (window.pollEvent(event))
//		{
//			if (event.type == sf::Event::Closed)
//				window.close();
//			if (event.type == sf::Event::MouseButtonPressed)
//				up = 0;
//		}
//		window.clear(sf::Color::Black);
//		shade.update(seconds);
//
//		window.draw(text);
//		window.draw(shade.getGradient());
//		window.draw(shade.getUpper());
//		window.draw(shade.getLower());
//		window.display();
//	}
//
//
//
//	return 0;
//}