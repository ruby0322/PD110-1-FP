#include "SceneManager.hpp"

SceneManager::SceneManager()
{
	setScene(SceneManager::SCENE_BATTLE);
	map.setTargets(&items, &projectiles, &players);
}

SceneManager::~SceneManager()
{
	for (size_t i = 0; i < entities.size(); ++i)
		delete[] entities[i];
	for (size_t i = 0; i < texts.size(); ++i)
		delete texts[i];
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

int SceneManager::getScene() const
{
	return currScene;
}

void SceneManager::updateBattle(float deltaTime)
{
	map.update(deltaTime);
	clearDeadProjectiles();
	clearDeadItems();
	for (auto& player : players)
		player->update(deltaTime);
	for (auto& item : items)
		item->update(deltaTime);
	for (auto& projectile : projectiles)
		projectile->update(deltaTime);
	for (auto& uiElement : uiElements)
		uiElement->update();
	players[0]->getCollider().checkCollision(players[1]->getCollider(), .5f);
}

void SceneManager::updateMainMenu(float deltaTime)
{
	for (size_t i = 0; i < mainMenuEntities.size(); ++i)
	{
		auto& entity = mainMenuEntities[i];
		entity->update(deltaTime);
	}
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
	for (size_t i = 0; i < mainMenuEntities.size(); ++i)
	{
		auto& entity = mainMenuEntities[i];
		entity->handleEvent(event);
	}
}

void SceneManager::handleEvent(const sf::Event& event)
{
	switch (currScene)
	{
		case SceneManager::SCENE_BATTLE:
			handleEventBattle(event);
			break;
		case SceneManager::SCENE_MAIN_MENU:
			handleEventMainMenu(event);
			break;
		default:
			break;
	}
}

void SceneManager::newRound(int mapNumber)
{
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
}

void SceneManager::renderSceneBuffer()
{
	// for (const auto& text : texts)
	// 	sceneBuffer.draw(*text);
	switch (currScene)
	{
		case SceneManager::SCENE_MAIN_MENU:
			break;
		case SceneManager::SCENE_HOW_TO_PLAY:
			break;
		case SceneManager::SCENE_BATTLE:
			sceneBuffer.clear(sf::Color(94, 196, 183));
			map.draw(sceneBuffer);
			for (const auto& player : players)
				sceneBuffer.draw(player->sprite);
			for (const auto& item : items)
				sceneBuffer.draw(item->sprite);
			for (const auto& projectile : projectiles)
				sceneBuffer.draw(projectile->sprite);

			break;
		case SceneManager::SCENE_WIN:
			break;
		case SceneManager::SCENE_VICTORY:
			break;
		case SceneManager::SCENE_PAUSE:
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
	window.setView(window.getDefaultView());
	window.clear(sf::Color(31, 30, 28));
	sf::Sprite sceneSprite = getSceneSprite();
	window.setView(playerOneView);
	window.draw(sceneSprite);
	window.setView(playerTwoView);
	window.draw(sceneSprite);
	window.setView(miniMap);
	window.draw(sceneSprite);

	window.setView(window.getDefaultView());
	if (currScene == SceneManager::SCENE_BATTLE)
		for (const auto& uiElement : uiElements)
			uiElement->draw(window);
	// draw UI elements
}

sf::Sprite SceneManager::getSceneSprite()
{
	renderSceneBuffer();
	return sf::Sprite(sceneBuffer.getTexture());
}