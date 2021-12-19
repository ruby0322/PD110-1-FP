#include "App.hpp"
#include "Platform/Platform.hpp"
#include <vector>

App::App()
{
}

App::~App()
{
}

void App::drawEntities()
{
	buffer.clear();
	for (auto& entity : entities)
	{
		buffer.draw(entity->sprite);
	}
	buffer.display();
	window.clear();
	window.draw(sf::Sprite(buffer.getTexture()));
	window.display();
}

void App::updateEntities(sf::Event event)
{
	for (auto& entity : entities)
		entity->update(event);
}

void App::init(float windowWidth = 400.f,
	float windowHeight = 400.f,
	const char* windowCaption = nullptr)
{
	float screenScalingFactor = platform.getScreenScalingFactor(window.getSystemHandle());
	// Use the screenScalingFactor
	window.create(sf::VideoMode(windowWidth * screenScalingFactor, windowHeight * screenScalingFactor), windowCaption);
	platform.setIcon(window.getSystemHandle());
	buffer.create(windowWidth, windowHeight);
}

void App::run()
{
	sf::Texture tex;
	tex.loadFromFile("content/Giardia1.png");

	sf::Sprite playerSprite;
	playerSprite.setTexture(tex, true);
	Player player(playerSprite);
	entities.push_back(&player);

	sf::Event event;
	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		while (window.pollEvent(event))
		{
			this->updateEntities(event);
			switch (event.type)
			{
				case sf::Event::Closed:
					window.close();
					break;
				default:
					break;
			}
		}
		this->drawEntities();
	}
}
