#include "App.h"

Application::Application() : mWindow(sf::VideoMode(WindowWidth, WindowHeight), "The Matrix Rain", sf::Style::Default)
{
	if (!font.loadFromFile("Kahless2p.ttf"))
		this->~Application();
	else
	{
		sf::Color green = sf::Color::Green;
		Matrix_Drop::setFontAndColor(font, green);
		Matrix_Drop::assign(RAIN_DROPS);
	}
}

Application::~Application()
{
	mWindow.close();
}

void Application::run()
{
	sf::Clock clock;
	while (mWindow.isOpen())
	{
		sf::Time deltaTime = clock.restart();
		processEvents();
		update(deltaTime);
		render();
	}
}

void Application::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			mWindow.close();
		case (sf::Event::KeyPressed): 
			if (event.key.code == sf::Keyboard::Escape)
			mWindow.close();
		}
	}
}

void Application::update(sf::Time deltaTime)
{
	for (int i = 0; i < RAIN_DROPS; i++)	
		Matrix_Drop::S_Array[i].update(deltaTime);
}

void Application::render()
{
	mWindow.clear(sf::Color::Black);
	for (int i = 0; i < RAIN_DROPS; i++)
	{
		mWindow.draw(Matrix_Drop::S_Array[i].getText());
		mWindow.draw(Matrix_Drop::S_Array[i].getShader()->getGradient());
		mWindow.draw(Matrix_Drop::S_Array[i].getShader()->getUpper());
		mWindow.draw(Matrix_Drop::S_Array[i].getShader()->getLower());
	}
	mWindow.display();
}