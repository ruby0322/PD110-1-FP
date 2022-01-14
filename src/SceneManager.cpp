#include "SceneManager.hpp"

SceneManager::SceneManager()
{
	currMap = 1;
	buttonEvent = Button::EVENT_NONE;
	setScene(SceneManager::SCENE_MAIN_MENU);
	map.setTargets(&items, &projectiles, &players);

}

SceneManager::~SceneManager()
{
	for (size_t i = 0; i < battleUiElements.size(); ++i)
		delete battleUiElements[i];
	for (size_t i = 0; i < mainMenuUiElements.size(); ++i)
		delete mainMenuUiElements[i];
	for (size_t i = 0; i < howToPlayUiElements.size(); ++i)
		delete howToPlayUiElements[i];
	for (size_t i = 0; i < pauseUiElements.size(); ++i)
		delete pauseUiElements[i];
	for (size_t i = 0; i < winUiElements.size(); ++i)
		delete winUiElements[i];
	for (size_t i = 0; i < victoryUiElements.size(); ++i)
		delete victoryUiElements[i];
	for (size_t i = 0; i < chooseMapUiElements.size(); ++i)
		delete chooseMapUiElements[i];
	for (size_t i = 0; i < miniMapUiElements.size(); ++i)
		delete miniMapUiElements[i];
	for (size_t i = 0; i < mainMenuButtons.size(); ++i)
		delete mainMenuButtons[i];
	for (size_t i = 0; i < howToPlayButtons.size(); ++i)
		delete howToPlayButtons[i];
	for (size_t i = 0; i < pauseButtons.size(); ++i)
		delete pauseButtons[i];
	for (size_t i = 0; i < winButtons.size(); ++i)
		delete winButtons[i];
	for (size_t i = 0; i < victoryButtons.size(); ++i)
		delete victoryButtons[i];
	for (size_t i = 0; i < chooseMapButtons.size(); ++i)
		delete chooseMapButtons[i];

	clearPlayers();
	clearItems();
	clearProjectiles();

}

void SceneManager::init(float windowWidth, float windowHeight)
{
	playerOneView.setSize(sf::Vector2f(240.f, 336.f));
	playerOneView.setCenter(sf::Vector2f(0.f, 0.f));
	playerOneView.setViewport(sf::FloatRect(-0.005f, .3f, 0.5f, .7f));
	playerTwoView.setSize(sf::Vector2f(240.f, 336.f));
	playerTwoView.setCenter(sf::Vector2f(0.f, 0.f));
	playerTwoView.setViewport(sf::FloatRect(.505f, .3f, 0.5f, .7f));
	miniMap.setSize(sf::Vector2f(windowWidth, windowHeight));
	miniMap.setCenter(sf::Vector2f(windowWidth / 2.f, windowHeight / 2.f));
	miniMap.setViewport(sf::FloatRect(.36f, .016f, .28f, .28f));
	sceneBuffer.create(windowWidth, windowHeight);

	sf::Vector2f border(windowWidth, windowHeight);

	Player* player1 = new Player(border, 1, &projectiles);
	Player* player2 = new Player(border, 2, &projectiles);

	players.push_back(player1);
	players.push_back(player2);

	UIElement* playerOnePhoto = new UIElement(UIElement::TYPE_PLAYER_ONE_PHOTO, player1, sf::Vector2f(0.f, 0.f));
	UIElement* playerTwoPhoto = new UIElement(UIElement::TYPE_PLAYER_TWO_PHOTO, player2, sf::Vector2f(0.f, 0.f));
	UIElement* playerOneHealthBar = new UIElement(UIElement::TYPE_PLAYER_ONE_HEALTH_BAR, player1, sf::Vector2f(0.f, 0.f));
	UIElement* playerTwoHealthBar = new UIElement(UIElement::TYPE_PLAYER_TWO_HEALTH_BAR, player2, sf::Vector2f(0.f, 0.f));
	UIElement* playerOneHealthBarBg = new UIElement(UIElement::TYPE_PLAYER_ONE_HEALTH_BAR_BG, player1, sf::Vector2f(0.f, 0.f));
	UIElement* playerTwoHealthBarBg = new UIElement(UIElement::TYPE_PLAYER_TWO_HEALTH_BAR_BG, player2, sf::Vector2f(0.f, 0.f));
	UIElement* playerOneHealing = new UIElement(UIElement::TYPE_PLAYER_ONE_HEALING, player1, sf::Vector2f(0.f, 0.f));
	UIElement* playerTwoHealing = new UIElement(UIElement::TYPE_PLAYER_TWO_HEALING, player2, sf::Vector2f(0.f, 0.f));
	UIElement* playerOneSpeedBoosted = new UIElement(UIElement::TYPE_PLAYER_ONE_SPEED_BOOSTED, player1, sf::Vector2f(0.f, 0.f));
	UIElement* playerTwoSpeedBoosted = new UIElement(UIElement::TYPE_PLAYER_TWO_SPEED_BOOSTED, player2, sf::Vector2f(0.f, 0.f));
	UIElement* playerOneBulletBoosted = new UIElement(UIElement::TYPE_PLAYER_ONE_BULLET_BOOSTED, player1, sf::Vector2f(0.f, 0.f));
	UIElement* playerTwoBulletBoosted = new UIElement(UIElement::TYPE_PLAYER_TWO_BULLET_BOOSTED, player2, sf::Vector2f(0.f, 0.f));
	UIElement* mainMenuBg = new UIElement(UIElement::TYPE_MAIN_MENU_BG, player1, sf::Vector2f(0.f, 0.f));
	UIElement* blueBodyCover = new UIElement(UIElement::TYPE_BLUE_BODY_COVER, player1, sf::Vector2f(0.f, 0.f));
	UIElement* redBodyCover = new UIElement(UIElement::TYPE_RED_BODY_COVER, player2, sf::Vector2f(0.f, 0.f));
	UIElement* blueBarrelCover = new UIElement(UIElement::TYPE_BLUE_BARREL_COVER, player1, sf::Vector2f(0.f, 0.f));
	UIElement* redBarrelCover = new UIElement(UIElement::TYPE_RED_BARREL_COVER, player2, sf::Vector2f(0.f, 0.f));
	UIElement* mainMenuTitle = new UIElement(UIElement::TYPE_MAIN_MENU_TITLE, player1, sf::Vector2f(0.f, 0.f));
	UIElement* howToPlayInstructions = new UIElement(UIElement::TYPE_HOW_TO_PLAY_INSTRUCTIONS, sf::Vector2f(0.f, 0.f));
	UIElement* winPlayerOnePhoto = new UIElement(UIElement::TYPE_WIN_PLAYER_ONE_PHOTO, sf::Vector2f(0.f, 0.f));
	UIElement* winPlayerTwoPhoto = new UIElement(UIElement::TYPE_WIN_PLAYER_TWO_PHOTO, sf::Vector2f(0.f, 0.f));
	UIElement* winText = new UIElement(UIElement::TYPE_WIN_TEXT, sf::Vector2f(0.f, 0.f));
	UIElement* victoryText = new UIElement(UIElement::TYPE_VICTORY_TEXT, sf::Vector2f(0.f, 0.f));
	UIElement* playerOneWinLightOne = new UIElement(UIElement::TYPE_PLAYER_WIN_LIGHT_ONE, player1, sf::Vector2f(UIElement::PLAYER_PHOTO_SIZE + 52.f, 30.f));
	UIElement* playerOneWinLightTwo = new UIElement(UIElement::TYPE_PLAYER_WIN_LIGHT_TWO, player1, sf::Vector2f(UIElement::PLAYER_PHOTO_SIZE + 32.f + 52.f, 30.f));
	UIElement* playerOneWinLightThree = new UIElement(UIElement::TYPE_PLAYER_WIN_LIGHT_THREE, player1, sf::Vector2f(UIElement::PLAYER_PHOTO_SIZE + 64.f + 52.f, 30.f));
	UIElement* playerTwoWinLightOne = new UIElement(UIElement::TYPE_PLAYER_WIN_LIGHT_ONE, player2, sf::Vector2f(960.f - UIElement::PLAYER_PHOTO_SIZE - 52.f, 30.f));
	UIElement* playerTwoWinLightTwo = new UIElement(UIElement::TYPE_PLAYER_WIN_LIGHT_TWO, player2, sf::Vector2f(928.f - UIElement::PLAYER_PHOTO_SIZE - 52.f, 30.f));
	UIElement* playerTwoWinLightThree = new UIElement(UIElement::TYPE_PLAYER_WIN_LIGHT_THREE, player2, sf::Vector2f(896.f - UIElement::PLAYER_PHOTO_SIZE - 52.f, 30.f));
	UIElement* pauseText = new UIElement(UIElement::TYPE_PAUSE_TEXT, sf::Vector2f(480.f, 320.f));
	UIElement* mapPreview = new UIElement(UIElement::TYPE_CHOOSE_MAP_PREVIEW, &currMap, sf::Vector2f(480.f, 460.f));
	UIElement* playerOneArrow = new UIElement(UIElement::TYPE_PLAYER_ONE_ARROW, player1, sf::Vector2f(0.f, 0.f));
	UIElement* playerTwoArrow = new UIElement(UIElement::TYPE_PLAYER_TWO_ARROW, player2, sf::Vector2f(0.f, 0.f));
	UIElement* chooseMapText = new UIElement(UIElement::TYPE_CHOOSE_MAP_TEXT, sf::Vector2f(480.f, 65.f));

	Button* mainMenuPlayButton = new Button(Button::TYPE_PLAY, &buttonEvent, sf::Vector2f(480.f, 710.f));
	Button* mainMenuInfoButton = new Button(Button::TYPE_INFO, &buttonEvent, sf::Vector2f(480.f, 850.f));
	Button* howToPlayCrossButton = new Button(Button::TYPE_HOW_TO_PLAY_BACK, &buttonEvent, sf::Vector2f(800.f, 100.f));

	Button* pauseBackButton = new Button(Button::TYPE_PAUSE_BACK, &buttonEvent, sf::Vector2f(200.f, 650.f));
	Button* pauseButton = new Button(Button::TYPE_PAUSE, &buttonEvent, sf::Vector2f(480.f, 650.f));
	Button* pauseResetButton = new Button(Button::TYPE_PAUSE_RESET, &buttonEvent, sf::Vector2f(760.f, 650.f));

	Button* winPlayButton = new Button(Button::TYPE_PLAY, &buttonEvent, sf::Vector2f(480.f, 850.f));

	Button* victoryResetButton = new Button(Button::TYPE_VICTORY_RESET, &buttonEvent, sf::Vector2f(480.f, 850.f));

	Button* chooseMapPrevButton = new Button(Button::TYPE_CHOOSE_MAP_PREV, &buttonEvent, sf::Vector2f(200.f, 890.f));
	Button* chooseMapNextButton = new Button(Button::TYPE_CHOOSE_MAP_NEXT, &buttonEvent, sf::Vector2f(760.f, 890.f));
	Button* chooseMapPlayButton = new Button(Button::TYPE_CHOOSE_MAP_PLAY, &buttonEvent, sf::Vector2f(480.f, 890.f));

	battleUiElements.push_back(playerOnePhoto);
	battleUiElements.push_back(playerTwoPhoto);
	battleUiElements.push_back(playerOneHealthBar);
	battleUiElements.push_back(playerTwoHealthBar);
	battleUiElements.push_back(playerOneHealthBarBg);
	battleUiElements.push_back(playerTwoHealthBarBg);
	battleUiElements.push_back(playerOneHealing);
	battleUiElements.push_back(playerTwoHealing);
	battleUiElements.push_back(playerOneSpeedBoosted);
	battleUiElements.push_back(playerTwoSpeedBoosted);
	battleUiElements.push_back(playerOneBulletBoosted);
	battleUiElements.push_back(playerTwoBulletBoosted);
	battleUiElements.push_back(playerOneWinLightOne);
	battleUiElements.push_back(playerOneWinLightTwo);
	battleUiElements.push_back(playerOneWinLightThree);
	battleUiElements.push_back(playerTwoWinLightOne);
	battleUiElements.push_back(playerTwoWinLightTwo);
	battleUiElements.push_back(playerTwoWinLightThree);

	mainMenuUiElements.push_back(mainMenuBg);
	mainMenuUiElements.push_back(blueBarrelCover);
	mainMenuUiElements.push_back(redBarrelCover);
	mainMenuUiElements.push_back(blueBodyCover);
	mainMenuUiElements.push_back(redBodyCover);
	mainMenuUiElements.push_back(mainMenuTitle);
	mainMenuButtons.push_back(mainMenuPlayButton);
	mainMenuButtons.push_back(mainMenuInfoButton);

	howToPlayUiElements.push_back(howToPlayInstructions);
	howToPlayButtons.push_back(howToPlayCrossButton);

	pauseUiElements.push_back(pauseText);

	pauseButtons.push_back(pauseButton);
	pauseButtons.push_back(pauseBackButton);
	pauseButtons.push_back(pauseResetButton);

	winUiElements.push_back(winPlayerOnePhoto);
	winUiElements.push_back(winPlayerTwoPhoto);
	winUiElements.push_back(winText);
	winButtons.push_back(winPlayButton);

	victoryUiElements.push_back(winPlayerOnePhoto);
	victoryUiElements.push_back(winPlayerTwoPhoto);
	victoryUiElements.push_back(victoryText);
	victoryButtons.push_back(victoryResetButton);

	chooseMapUiElements.push_back(mapPreview);
	chooseMapUiElements.push_back(chooseMapText);
	chooseMapButtons.push_back(chooseMapNextButton);
	chooseMapButtons.push_back(chooseMapPrevButton);
	chooseMapButtons.push_back(chooseMapPlayButton);

	miniMapUiElements.push_back(playerOneArrow);
	miniMapUiElements.push_back(playerTwoArrow);

}

void SceneManager::clearItems()
{
	for (size_t i = 0; i < items.size(); ++i)
		delete items[i];
	items.clear();
}

void SceneManager::clearProjectiles()
{
	for (size_t i = 0; i < projectiles.size(); ++i)
		delete projectiles[i];
	projectiles.clear();
}

void SceneManager::clearPlayers()
{
	for (size_t i = 0; i < players.size(); ++i)
		delete players[i];
	players.clear();
}

void SceneManager::clearDeadProjectiles()
{
	for (size_t i = 0; i < projectiles.size(); ++i)
	{
		if (projectiles[i]->isDead())
		{
			delete projectiles[i];
			projectiles.erase(projectiles.begin() + i--);
		}
	}
}

void SceneManager::clearDeadItems()
{
	for (size_t i = 0; i < items.size(); ++i)
	{
		if (items[i]->isDead())
		{
			delete items[i];
			items.erase(items.begin() + i--);
		}
	}
}

sf::Vector2f SceneManager::fixCameraCenter(const sf::Vector2f& pos)
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

void SceneManager::updateCameras()
{
	playerOneView.setCenter(fixCameraCenter(players[0]->sprite.getPosition()));
	playerTwoView.setCenter(fixCameraCenter(players[1]->sprite.getPosition()));
}

void SceneManager::setScene(int newScene)
{
	currScene = newScene;
}

int& SceneManager::getScene()
{
	return currScene;
}

void SceneManager::handleButtonEvent()
{
	switch (buttonEvent)
	{
		case Button::EVENT_NEW_ROUND:
			newRound(currMap);
			setScene(SceneManager::SCENE_BATTLE);
			break;
		case Button::EVENT_CHOOSE_MAP:
			setScene(SceneManager::SCENE_CHOOSE_MAP);
			break;
		case Button::EVENT_NEW_GAME:
			setScene(SceneManager::SCENE_MAIN_MENU);
			for (auto& player : players)
				player->newGame();
			break;
		case Button::EVENT_HOW_TO_PLAY:
			setScene(SceneManager::SCENE_HOW_TO_PLAY);
			break;
		case Button::EVENT_MAIN_MENU:
			setScene(SceneManager::SCENE_MAIN_MENU);
			break;
		case Button::EVENT_PAUSE_RESUME:
			setScene(SceneManager::SCENE_BATTLE);
			break;
		case Button::EVENT_BATTLE:
			setScene(SceneManager::SCENE_BATTLE);
			break;
		case Button::EVENT_NEXT_MAP:
			if (++currMap > 9) currMap -= 9;
			break;
		case Button::EVENT_PREV_MAP:
			if (--currMap < 1) currMap += 9;
			break;
		default:
			break;
	}
	buttonEvent = Button::EVENT_NONE;
}

void SceneManager::updateBattle(float deltaTime)
{
	map.update(deltaTime);
	clearDeadProjectiles();
	clearDeadItems();
	for (auto& player : players)
	{
		if (player->isDead())
		{
			players[player->getNumber() % 2]->win();
			winnerOfTheRound = player->getNumber() % 2;
			setScene(SceneManager::SCENE_WIN);
			if (players[player->getNumber() % 2]->isVictorious())
			{
				setScene(SceneManager::SCENE_VICTORY);
				SoundManager::PlaySoundEffect(SoundManager::TYPE_VICTORY);
			}
			else
				SoundManager::PlaySoundEffect(SoundManager::TYPE_WIN);
			return;
		}
		player->update(deltaTime);
	}
	for (auto& item : items)
		item->update(deltaTime);
	for (auto& projectile : projectiles)
		projectile->update(deltaTime);
	for (auto& elem : battleUiElements)
		elem->update(deltaTime);
	for (auto& elem : miniMapUiElements)
		elem->update(deltaTime);
	players[0]->getCollider().checkCollision(players[1]->getCollider(), .5f);
}

void SceneManager::updateMainMenu(float deltaTime)
{
	for (auto& elem : mainMenuUiElements)
		elem->update(deltaTime);
}

void SceneManager::updateChooseMap(float deltaTime)
{
	for (auto& elem : chooseMapUiElements)
		elem->update(deltaTime);
}

void SceneManager::update(float deltaTime)
{
	switch (currScene)
	{
		case SceneManager::SCENE_BATTLE:
			updateBattle(deltaTime);
			break;
		case SceneManager::SCENE_MAIN_MENU:
			updateMainMenu(deltaTime);
			break;
		case SceneManager::SCENE_CHOOSE_MAP:
			updateChooseMap(deltaTime);
			break;
		default:
			break;
	}
	updateCameras();
}

void SceneManager::handleEventBattle(const sf::Event& event)
{
	for (auto& player : players)
		player->handleEvent(event);
	for (auto& item : items)
		item->handleEvent(event);
	for (auto& projectile : projectiles)
		projectile->handleEvent(event);
}

void SceneManager::handleEventMainMenu(const sf::Event& event)
{
	for (auto& button : mainMenuButtons)
		button->handleEvent(event);
}

void SceneManager::handleEventHowToPlay(const sf::Event& event)
{
	for (auto& button : howToPlayButtons)
		button->handleEvent(event);
}

void SceneManager::handleEventPause(const sf::Event& event)
{
	for (auto& button : pauseButtons)
		button->handleEvent(event);
}

void SceneManager::handleEventWin(const sf::Event& event)
{
	for (auto& button : winButtons)
		button->handleEvent(event);
}

void SceneManager::handleEventVictory(const sf::Event& event)
{
	for (auto& button : victoryButtons)
		button->handleEvent(event);
}

void SceneManager::handleEventChooseMap(const sf::Event& event)
{
	for (auto& btn : chooseMapButtons)
		btn->handleEvent(event);
}

void SceneManager::handleEvent(const sf::Event& event)
{
	switch (currScene)
	{
		case SceneManager::SCENE_BATTLE:
			handleEventBattle(event);
			switch (event.type)
			{
				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::Space)
					{
						setScene(SceneManager::SCENE_PAUSE);
						SoundManager::PlaySoundEffect(SoundManager::TYPE_BUTTON_PRESSED);
					}
					break;
				default:
					break;
			}
			break;
		case SceneManager::SCENE_MAIN_MENU:
			handleEventMainMenu(event);
			break;
		case SceneManager::SCENE_HOW_TO_PLAY:
			handleEventHowToPlay(event);
			break;
		case SceneManager::SCENE_PAUSE:
			switch (event.type)
			{
				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::Space)
					{
						setScene(SceneManager::SCENE_BATTLE);
						SoundManager::PlaySoundEffect(SoundManager::TYPE_BUTTON_PRESSED);
					}
					break;
				default:
					break;
			}
			handleEventPause(event);
			break;
		case SceneManager::SCENE_WIN:
			handleEventWin(event);
			break;
		case SceneManager::SCENE_VICTORY:
			handleEventVictory(event);
			break;
		case SceneManager::SCENE_CHOOSE_MAP:
			handleEventChooseMap(event);
			break;
		default:
			break;
	}
	handleButtonEvent();
}

void SceneManager::newRound(int mapNumber)
{
	clearItems();
	clearProjectiles();
	int matrix[30][30];
	std::string filePath = "content/map/map" + std::to_string(mapNumber) + ".txt";
	MapManager::LoadMapFromFile(matrix, filePath);
	map.loadMap(matrix);

	sf::Vector2f playerOnePos;
	sf::Vector2f playerTwoPos;

	for (const auto& tile : map.getTiles())
		if (tile->getType() == Tile::TYPE_SPAWNPOINT_ONE)
		{
			playerOnePos = tile->getSprite().getPosition();
			break;
		}
	for (const auto& tile : map.getTiles())
		if (tile->getType() == Tile::TYPE_SPAWNPOINT_TWO)
		{
			playerTwoPos = tile->getSprite().getPosition();
			break;
		}

	players[0]->reset(playerOnePos);
	players[1]->reset(playerTwoPos);
	currMap = mapNumber;
}

void SceneManager::renderSceneBuffer()
{
	// for (const auto& text : texts)
	// 	sceneBuffer.draw(*text);
	switch (currScene)
	{
		case SceneManager::SCENE_MAIN_MENU:
			sceneBuffer.clear(sf::Color(94, 196, 183));
			for (const auto& elem : mainMenuUiElements)
				elem->draw(sceneBuffer);
			for (const auto& button : mainMenuButtons)
				button->draw(sceneBuffer);
			break;
		case SceneManager::SCENE_HOW_TO_PLAY:
			sceneBuffer.clear(sf::Color(94, 196, 183));
			for (const auto& elem : mainMenuUiElements)
				elem->draw(sceneBuffer);
			for (const auto& button : mainMenuButtons)
				button->draw(sceneBuffer);
			sceneBuffer.clear(sf::Color(0, 0, 0, 10));
			for (const auto& elem : howToPlayUiElements)
				elem->draw(sceneBuffer);
			for (const auto& button : howToPlayButtons)
				button->draw(sceneBuffer);
			break;
		case SceneManager::SCENE_BATTLE:
			sceneBuffer.clear(sf::Color(94, 196, 183));
			map.draw(sceneBuffer);
			for (const auto& item : items)
				item->draw(sceneBuffer);
			for (const auto& player : players)
				player->draw(sceneBuffer);
			for (const auto& projectile : projectiles)
				projectile->draw(sceneBuffer);
			break;
		case SceneManager::SCENE_WIN:
			break;
		case SceneManager::SCENE_VICTORY:
			break;
		case SceneManager::SCENE_PAUSE:
			sceneBuffer.clear(sf::Color(94, 196, 183));
			map.draw(sceneBuffer);
			for (const auto& item : items)
				item->draw(sceneBuffer);
			for (const auto& player : players)
				player->draw(sceneBuffer);
			for (const auto& projectile : projectiles)
				projectile->draw(sceneBuffer);
			break;
		case SceneManager::SCENE_QUIT:
			break;
		case SceneManager::SCENE_END:
			break;

		default:
			break;
	}
	sceneBuffer.display();
}

void SceneManager::renderWindow(sf::RenderWindow& window)
{
	sf::Sprite sceneSprite = getSceneSprite();
	switch (currScene)
	{
		case SceneManager::SCENE_BATTLE:
			window.setView(window.getDefaultView());
			window.clear(sf::Color(31, 30, 28));
			window.setView(playerOneView);
			window.draw(sceneSprite);
			window.setView(playerTwoView);
			window.draw(sceneSprite);
			window.setView(miniMap);
			window.draw(sceneSprite);
			for (const auto& elem : miniMapUiElements)
				elem->draw(window);

			window.setView(window.getDefaultView());
			for (const auto& elem : battleUiElements)
				elem->draw(window);
			break;
		case SceneManager::SCENE_MAIN_MENU:
			window.setView(window.getDefaultView());
			window.draw(sceneSprite);
			break;
		case SceneManager::SCENE_HOW_TO_PLAY:
			window.setView(window.getDefaultView());
			window.draw(sceneSprite);
			break;
		case SceneManager::SCENE_PAUSE:
			window.setView(window.getDefaultView());
			window.clear(sf::Color(31, 30, 28));
			window.setView(playerOneView);
			window.draw(sceneSprite);
			window.setView(playerTwoView);
			window.draw(sceneSprite);
			window.setView(miniMap);
			window.draw(sceneSprite);

			window.setView(window.getDefaultView());
			for (const auto& elem : battleUiElements)
				elem->draw(window);
			window.clear(sf::Color(42, 43, 43));
			for (const auto& elem : pauseUiElements)
				elem->draw(window);
			for (const auto& btn : pauseButtons)
				btn->draw(window);
			break;
		case SceneManager::SCENE_WIN:
			window.setView(window.getDefaultView());
			window.clear(sf::Color(31, 30, 28));
			window.setView(playerOneView);
			window.draw(sceneSprite);
			window.setView(playerTwoView);
			window.draw(sceneSprite);
			window.setView(miniMap);
			window.draw(sceneSprite);

			window.setView(window.getDefaultView());
			for (const auto& elem : battleUiElements)
				elem->draw(window);

			window.clear(sf::Color(0, 0, 0));
			winUiElements[winnerOfTheRound]->draw(window);
			for (const auto& btn : winButtons)
				btn->draw(window);
			winUiElements[2]->draw(window);
			break;
		case SceneManager::SCENE_VICTORY:
			window.setView(window.getDefaultView());
			window.clear(sf::Color(31, 30, 28));
			window.setView(playerOneView);
			window.draw(sceneSprite);
			window.setView(playerTwoView);
			window.draw(sceneSprite);
			window.setView(miniMap);
			window.draw(sceneSprite);

			window.setView(window.getDefaultView());
			for (const auto& elem : battleUiElements)
				elem->draw(window);

			window.clear(sf::Color(0, 0, 0));
			victoryUiElements[winnerOfTheRound]->draw(window);
			for (const auto& btn : victoryButtons)
				btn->draw(window);
			victoryUiElements[2]->draw(window);
			break;
		case SceneManager::SCENE_CHOOSE_MAP:
			window.clear(sf::Color(42, 43, 43));
			for (const auto& elem : chooseMapUiElements)
				elem->draw(window);
			for (const auto& btn : chooseMapButtons)
				btn->draw(window);
			break;
		default:
			break;
	}
	// draw UI elements
}

sf::Sprite SceneManager::getSceneSprite()
{
	renderSceneBuffer();
	return sf::Sprite(sceneBuffer.getTexture());
}