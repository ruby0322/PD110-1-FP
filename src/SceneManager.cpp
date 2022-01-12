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

void SceneManager::setBufferSize(int width, int height)
{
	sceneBuffer.create(width, height);
}

void SceneManager::setScene(int newScene)
{
	currScene = newScene;
}

int SceneManager::getScene() const
{
	return currScene;
}

void SceneManager::updateBattle(float deltaTime) {
	map.update(deltaTime);
	for (size_t i = 0; i < entities.size(); ++i)
	{
		auto& entity = entities[i];
		entity->update(deltaTime);
	}
	players[0]->getCollider().checkCollision(players[1]->getCollider(), .5f);
}

void SceneManager::updateMainMenu(float deltaTime) {
	for (size_t i = 0; i < mainMenuEntities.size(); ++i)
	{
		auto& entity = mainMenuEntities[i];
		entity->update(deltaTime);
	}
}

void SceneManager::update(float deltaTime) {
	switch (currScene) {
		case SceneManager::SCENE_BATTLE:
		updateBattle(deltaTime);
		break;
		case SceneManager::SCENE_MAIN_MENU:
		updateMainMenu(deltaTime);
		break;
		default:
		break;
	}
}

void SceneManager::handleEventBattle(const sf::Event& event) {
	for (size_t i = 0; i < entities.size(); ++i)
	{
		auto& entity = entities[i];
		entity->handleEvent(event);
	}
}

void SceneManager::handleEventMainMenu(const sf::Event& event) {
	for (size_t i = 0; i < mainMenuEntities.size(); ++i)
	{
		auto& entity = mainMenuEntities[i];
		entity->handleEvent(event);
	}
}

void SceneManager::handleEvent(const sf::Event& event)
{
	switch (currScene) {
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
			for (const auto& entity : entities)
				sceneBuffer.draw(entity->sprite);
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

sf::Sprite SceneManager::getSceneSprite()
{
	renderSceneBuffer();
	return sf::Sprite(sceneBuffer.getTexture());
}