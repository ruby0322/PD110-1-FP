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


	sf::Vector2f border(window.getSize().x, window.getSize().y);

	Player* player1 = new Player(border, 1, &sceneManager.projectiles);
	Player* player2 = new Player(border, 2, &sceneManager.projectiles);

	sceneManager.players.push_back(player1);
	sceneManager.players.push_back(player2);

	UIElement* playerOnePhoto = new UIElement(UIElement::TYPE_PLAYER_ONE_PHOTO, player1);
	UIElement* playerTwoPhoto = new UIElement(UIElement::TYPE_PLAYER_TWO_PHOTO, player2);
	UIElement* playerOneHealthBar = new UIElement(UIElement::TYPE_PLAYER_ONE_HEALTH_BAR, player1);
	UIElement* playerTwoHealthBar = new UIElement(UIElement::TYPE_PLAYER_TWO_HEALTH_BAR, player2);
	UIElement* playerOneHealthBarBg = new UIElement(UIElement::TYPE_PLAYER_ONE_HEALTH_BAR_BG, player1);
	UIElement* playerTwoHealthBarBg = new UIElement(UIElement::TYPE_PLAYER_TWO_HEALTH_BAR_BG, player2);
	UIElement* playerOneHealing = new UIElement(UIElement::TYPE_PLAYER_ONE_HEALING, player1);
	UIElement* playerTwoHealing = new UIElement(UIElement::TYPE_PLAYER_TWO_HEALING, player2);
	UIElement* playerOneSpeedBoosted = new UIElement(UIElement::TYPE_PLAYER_ONE_SPEED_BOOSTED, player1);
	UIElement* playerTwoSpeedBoosted = new UIElement(UIElement::TYPE_PLAYER_TWO_SPEED_BOOSTED, player2);
	UIElement* playerOneBulletBoosted = new UIElement(UIElement::TYPE_PLAYER_ONE_BULLET_BOOSTED, player1);
	UIElement* playerTwoBulletBoosted = new UIElement(UIElement::TYPE_PLAYER_TWO_BULLET_BOOSTED, player2);

	sceneManager.uiElements.push_back(playerOnePhoto);
	sceneManager.uiElements.push_back(playerTwoPhoto);
	sceneManager.uiElements.push_back(playerOneHealthBar);
	sceneManager.uiElements.push_back(playerTwoHealthBar);
	sceneManager.uiElements.push_back(playerOneHealthBarBg);
	sceneManager.uiElements.push_back(playerTwoHealthBarBg);
	sceneManager.uiElements.push_back(playerOneHealing);
	sceneManager.uiElements.push_back(playerTwoHealing);
	sceneManager.uiElements.push_back(playerOneSpeedBoosted);
	sceneManager.uiElements.push_back(playerTwoSpeedBoosted);
	sceneManager.uiElements.push_back(playerOneBulletBoosted);
	sceneManager.uiElements.push_back(playerTwoBulletBoosted);

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
