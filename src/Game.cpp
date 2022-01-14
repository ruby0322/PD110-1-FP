#include "Game.hpp"

Game::Game()
{
}

Game::~Game()
{
}

void Game::render()
{
	sceneManager.renderWindow(window);
	window.display();
}

void Game::init(float windowWidth = 400.f,
	float windowHeight = 400.f,
	const char* windowCaption = nullptr)
{
	SoundManager::Init();
	SoundManager::ToggleIntroMusic();
	// SoundManager::PlaySoundEffect(SoundManager::TYPE_FIRE_SHOT);

	window.create(sf::VideoMode(windowWidth, windowHeight), windowCaption, sf::Style::Titlebar | sf::Style::Close);
	platform.setIcon(window.getSystemHandle());
	sf::Image icon;
	icon.loadFromFile("content/Image/Tank/blue_tank_small.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	sceneManager.init(windowWidth, windowHeight);
}

void Game::__debug(const sf::Event& event)
{
	switch (event.type)
	{
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
				case sf::Keyboard::Num1:
					sceneManager.newRound(1);
					break;
				case sf::Keyboard::Num2:
					sceneManager.newRound(2);
					break;
				case sf::Keyboard::Num3:
					sceneManager.newRound(3);
					break;
				case sf::Keyboard::Num4:
					sceneManager.newRound(4);
					break;
				case sf::Keyboard::Num5:
					sceneManager.newRound(5);
					break;
				case sf::Keyboard::Num6:
					sceneManager.newRound(6);
					break;
				case sf::Keyboard::Num7:
					sceneManager.newRound(7);
					break;
				case sf::Keyboard::Num8:
					sceneManager.newRound(8);
					break;
				case sf::Keyboard::Num9:
					sceneManager.newRound(9);
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}
}

void Game::run()
{
	sf::Event event;
	float deltaTime;
	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		while (window.pollEvent(event))
		{
			sceneManager.handleEvent(event);
			switch (event.type)
			{
				case sf::Event::Closed:
					window.close();
					break;
				default:
					break;
			}
			__debug(event);
		}
		sceneManager.update(deltaTime);
		render();
	}
}
