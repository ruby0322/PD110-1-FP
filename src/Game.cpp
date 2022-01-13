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
	UIElement* mainMenuBg = new UIElement(UIElement::TYPE_MAIN_MENU_BG, player1);
	UIElement* blueBodyCover = new UIElement(UIElement::TYPE_BLUE_BODY_COVER, player1);
	UIElement* redBodyCover = new UIElement(UIElement::TYPE_RED_BODY_COVER, player2);
	UIElement* blueBarrelCover = new UIElement(UIElement::TYPE_BLUE_BARREL_COVER, player1);
	UIElement* redBarrelCover = new UIElement(UIElement::TYPE_RED_BARREL_COVER, player2);
	UIElement* mainMenuTitle = new UIElement(UIElement::TYPE_MAIN_MENU_TITLE, player1);
	UIElement* howToPlayInstructions = new UIElement(UIElement::TYPE_HOW_TO_PLAY_INSTRUCTIONS, nullptr);
	UIElement* winPlayerOnePhoto = new UIElement(UIElement::TYPE_WIN_PLAYER_ONE_PHOTO, nullptr);
	UIElement* winPlayerTwoPhoto = new UIElement(UIElement::TYPE_WIN_PLAYER_TWO_PHOTO, nullptr);
	UIElement* winText = new UIElement(UIElement::TYPE_WIN_TEXT, nullptr);
	UIElement* victoryText = new UIElement(UIElement::TYPE_VICTORY_TEXT, nullptr);

	Button* mainMenuPlayButton = new Button(Button::TYPE_PLAY, &sceneManager.getScene(), &sceneManager.buttonEvent, sf::Vector2f(480.f, 710.f));
	Button* mainMenuInfoButton = new Button(Button::TYPE_INFO, &sceneManager.getScene(), nullptr, sf::Vector2f(480.f, 850.f));
	Button* howToPlayCrossButton = new Button(Button::TYPE_HOW_TO_PLAY_BACK, &sceneManager.getScene(), nullptr, sf::Vector2f(800.f, 100.f));

	Button* pauseBackButton = new Button(Button::TYPE_PAUSE_BACK, &sceneManager.getScene(), nullptr, sf::Vector2f(200.f, 480.f));
	Button* pauseButton = new Button(Button::TYPE_PAUSE, &sceneManager.getScene(), nullptr, sf::Vector2f(480.f, 480.f));
	Button* pauseResetButton = new Button(Button::TYPE_PAUSE_RESET, &sceneManager.getScene(), &sceneManager.buttonEvent, sf::Vector2f(760.f, 480.f));

	Button* winPlayButton = new Button(Button::TYPE_PLAY, &sceneManager.getScene(), &sceneManager.buttonEvent, sf::Vector2f(480.f, 850.f));

	Button* victoryResetButton = new Button(Button::TYPE_VICTORY_RESET, &sceneManager.getScene(), &sceneManager.buttonEvent, sf::Vector2f(480.f, 850.f));

	sceneManager.battleUiElements.push_back(playerOnePhoto);
	sceneManager.battleUiElements.push_back(playerTwoPhoto);
	sceneManager.battleUiElements.push_back(playerOneHealthBar);
	sceneManager.battleUiElements.push_back(playerTwoHealthBar);
	sceneManager.battleUiElements.push_back(playerOneHealthBarBg);
	sceneManager.battleUiElements.push_back(playerTwoHealthBarBg);
	sceneManager.battleUiElements.push_back(playerOneHealing);
	sceneManager.battleUiElements.push_back(playerTwoHealing);
	sceneManager.battleUiElements.push_back(playerOneSpeedBoosted);
	sceneManager.battleUiElements.push_back(playerTwoSpeedBoosted);
	sceneManager.battleUiElements.push_back(playerOneBulletBoosted);
	sceneManager.battleUiElements.push_back(playerTwoBulletBoosted);

	sceneManager.mainMenuUiElements.push_back(mainMenuBg);
	sceneManager.mainMenuUiElements.push_back(blueBarrelCover);
	sceneManager.mainMenuUiElements.push_back(redBarrelCover);
	sceneManager.mainMenuUiElements.push_back(blueBodyCover);
	sceneManager.mainMenuUiElements.push_back(redBodyCover);
	sceneManager.mainMenuUiElements.push_back(mainMenuTitle);
	sceneManager.mainMenuButtons.push_back(mainMenuPlayButton);
	sceneManager.mainMenuButtons.push_back(mainMenuInfoButton);

	sceneManager.howToPlayUiElements.push_back(howToPlayInstructions);
	sceneManager.howToPlayButtons.push_back(howToPlayCrossButton);

	sceneManager.pauseButtons.push_back(pauseButton);
	sceneManager.pauseButtons.push_back(pauseBackButton);
	sceneManager.pauseButtons.push_back(pauseResetButton);

	sceneManager.winUiElements.push_back(winPlayerOnePhoto);
	sceneManager.winUiElements.push_back(winPlayerTwoPhoto);
	sceneManager.winUiElements.push_back(winText);
	sceneManager.winButtons.push_back(winPlayButton);

	sceneManager.victoryUiElements.push_back(winPlayerOnePhoto);
	sceneManager.victoryUiElements.push_back(winPlayerTwoPhoto);
	sceneManager.victoryUiElements.push_back(victoryText);
	sceneManager.victoryButtons.push_back(victoryResetButton);

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
