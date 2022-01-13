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
	for (size_t i = 0; i < entities.size(); ++i)
		delete[] entities[i];
	for (size_t i = 0; i < texts.size(); ++i)
		delete texts[i];
	for (size_t i = 0; i < battleUiElements.size(); ++i)
		delete battleUiElements[i];
	for (size_t i = 0; i < mainMenuUiElements.size(); ++i)
		delete mainMenuUiElements[i];
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
			setScene(SceneManager::SCENE_BATTLE);
			newRound(Generator::RandInt(1, 9));
			std::cout << "..." << std::endl;
			break;
		case Button::EVENT_NEW_GAME:
			setScene(SceneManager::SCENE_MAIN_MENU);
			for (auto& player : players)
				player->newGame();
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
	for (auto& battleUiElement : battleUiElements)
		battleUiElement->update(deltaTime);
	players[0]->getCollider().checkCollision(players[1]->getCollider(), .5f);
}

void SceneManager::updateMainMenu(float deltaTime)
{
	for (auto& elem : mainMenuUiElements)
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
					if (event.key.code == sf::Keyboard::Escape)
					{
						setScene(SceneManager::SCENE_MAIN_MENU);
						SoundManager::PlaySoundEffect(SoundManager::TYPE_BUTTON_PRESSED);
					}
					if (event.key.code == sf::Keyboard::R)
					{
						newRound(currMap);
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
	std::string filePath = "map/map" + std::to_string(mapNumber) + ".txt";
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
	if (currScene == SceneManager::SCENE_BATTLE)
	{
		window.setView(window.getDefaultView());
		window.clear(sf::Color(31, 30, 28));
		window.setView(playerOneView);
		window.draw(sceneSprite);
		window.setView(playerTwoView);
		window.draw(sceneSprite);
		window.setView(miniMap);
		window.draw(sceneSprite);

		window.setView(window.getDefaultView());
		for (const auto& battleUiElement : battleUiElements)
			battleUiElement->draw(window);
	}
	else if (currScene == SceneManager::SCENE_MAIN_MENU)
	{
		window.setView(window.getDefaultView());
		window.draw(sceneSprite);
	}
	else if (currScene == SceneManager::SCENE_HOW_TO_PLAY)
	{
		window.setView(window.getDefaultView());
		window.draw(sceneSprite);
	}
	else if (currScene == SceneManager::SCENE_PAUSE)
	{
		window.setView(window.getDefaultView());
		window.clear(sf::Color(31, 30, 28));
		window.setView(playerOneView);
		window.draw(sceneSprite);
		window.setView(playerTwoView);
		window.draw(sceneSprite);
		window.setView(miniMap);
		window.draw(sceneSprite);

		window.setView(window.getDefaultView());
		for (const auto& battleUiElement : battleUiElements)
			battleUiElement->draw(window);
		window.clear(sf::Color(0, 0, 0, 0));
		for (const auto& button : pauseButtons)
			button->draw(window);
	}
	else if (currScene == SceneManager::SCENE_WIN)
	{
		window.setView(window.getDefaultView());
		window.clear(sf::Color(31, 30, 28));
		window.setView(playerOneView);
		window.draw(sceneSprite);
		window.setView(playerTwoView);
		window.draw(sceneSprite);
		window.setView(miniMap);
		window.draw(sceneSprite);

		window.setView(window.getDefaultView());
		for (const auto& battleUiElement : battleUiElements)
			battleUiElement->draw(window);

		window.clear(sf::Color(0, 0, 0, 2));
		winUiElements[winnerOfTheRound]->draw(window);
		for (const auto& button : winButtons)
			button->draw(window);
		winUiElements[2]->draw(window);
	}
	else if (currScene == SceneManager::SCENE_VICTORY)
	{
		window.setView(window.getDefaultView());
		window.clear(sf::Color(31, 30, 28));
		window.setView(playerOneView);
		window.draw(sceneSprite);
		window.setView(playerTwoView);
		window.draw(sceneSprite);
		window.setView(miniMap);
		window.draw(sceneSprite);

		window.setView(window.getDefaultView());
		for (const auto& battleUiElement : battleUiElements)
			battleUiElement->draw(window);

		window.clear(sf::Color(0, 0, 0, 2));
		victoryUiElements[winnerOfTheRound]->draw(window);
		for (const auto& button : victoryButtons)
			button->draw(window);
		victoryUiElements[2]->draw(window);

	}
	// draw UI elements
}

sf::Sprite SceneManager::getSceneSprite()
{
	renderSceneBuffer();
	return sf::Sprite(sceneBuffer.getTexture());
}