#include "Game.hpp"

Game::Game()
{
}

Game::~Game()
{

}

void Game::render()
{
	sf::Sprite sceneSprite = sceneManager.getSceneSprite();
	window.setView(playerOneView);
	window.draw(sceneSprite);
	window.setView(playerTwoView);
	window.draw(sceneSprite);
	window.setView(miniMap);
	window.draw(sceneSprite);

	// window.setView(window.getDefaultView());
	// draw UI elements

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
	sceneManager.setBufferSize(windowWidth, windowHeight);

	playerOneView.setSize(sf::Vector2f(240.f, 336.f));
	playerOneView.setCenter(sf::Vector2f(0.f, 0.f));
	playerOneView.setViewport(sf::FloatRect(-0.005f, .3f, 0.5f, .7f));
	playerTwoView.setSize(sf::Vector2f(240.f, 336.f));
	playerTwoView.setCenter(sf::Vector2f(0.f, 0.f));
	playerTwoView.setViewport(sf::FloatRect(.505f, .3f, 0.5f, .7f));
	miniMap.setSize(sf::Vector2f(windowWidth, windowHeight));
	miniMap.setCenter(sf::Vector2f(windowWidth / 2.f, windowHeight / 2.f));
	miniMap.setViewport(sf::FloatRect(.36f, .016f, .28f, .28f));



	sf::Vector2f border(window.getSize().x, window.getSize().y);

	Player* player1 = new Player(border, 1);
	Player* player2 = new Player(border, 2);

	sceneManager.players.push_back(player1);
	sceneManager.players.push_back(player2);

	// Item* newItem = new Item(0, sf::Vector2f(100.f, 100.f), &sceneManager.players);
	// sceneManager.items.push_back(newItem);
	sf::Texture tex;
	std::vector<sf::Texture> playButtonFrames;
	tex.loadFromFile("content/Image/Scene/MainMenu/PlayButton/Play_Pressed.png");
	playButtonFrames.push_back(tex);
	tex.loadFromFile("content/Image/Scene/MainMenu/PlayButton/Play_Unpressed.png");
	playButtonFrames.push_back(tex);
	// Button* playButton = new Button(playButtonFrames, Button::TYPE_PLAY, this);

	sceneManager.newRound(1);
	sceneManager.newRound(1);
}

sf::Vector2f Game::fixCameraCenter(const sf::Vector2f& pos)
{
	sf::Vector2f fixedPos(pos);

	if (pos.x < playerOneView.getSize().x / 2)
		fixedPos.x = playerOneView.getSize().x / 2;
	else if (pos.x > 960 - playerOneView.getSize().x / 2)
		fixedPos.x = 960 - playerOneView.getSize().x / 2;
	if (pos.y < playerOneView.getSize().y / 2)
		fixedPos.y = playerOneView.getSize().y / 2;
	else if (pos.y > 960 - playerOneView.getSize().y / 2)
		fixedPos.y = 960 - playerOneView.getSize().y / 2;

	return fixedPos;
}

void Game::updateCameras()
{
	playerOneView.setCenter(fixCameraCenter(sceneManager.players[0]->sprite.getPosition()));
	playerTwoView.setCenter(fixCameraCenter(sceneManager.players[1]->sprite.getPosition()));
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
		updateCameras();
		render();
	}
}
