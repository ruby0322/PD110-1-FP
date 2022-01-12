#include "Platform/Platform.hpp"
#include "Player.hpp"
#include "Entity.hpp"
#include "Item.hpp"
#include "Projectile.hpp"
#include "Map.hpp"
#include "MapManager.hpp"

#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

class SceneManager {
private:

	int currScene;
	sf::RenderTexture sceneBuffer;

	void renderSceneBuffer();
	void updateBattle(float deltaTime);
	void updateMainMenu(float deltaTime);
	void handleEventBattle(const sf::Event& event);
	void handleEventMainMenu(const sf::Event& event);
	void clearDeadProjectiles();
	void clearDeadItems();

public:

	static const int SCENE_MAIN_MENU = 0;
	static const int SCENE_HOW_TO_PLAY = 1;
	static const int SCENE_BATTLE = 2;
	static const int SCENE_PAUSE = 3;
	static const int SCENE_WIN = 4;
	static const int SCENE_VICTORY = 5;
	static const int SCENE_QUIT = 6;
	static const int SCENE_END = 7;

	std::vector<Entity*> mainMenuEntities;

	std::vector<Player*> players;
	std::vector<Entity*> entities;
	std::vector<Item*> items;
	std::vector<Projectile*> projectiles;
	std::vector<sf::Text*> texts;
	Map map;

	SceneManager();
	~SceneManager();

	void handleEvent(const sf::Event& event);
	void newRound(int mapNumber);
	void update(float deltaTime);
	void setScene(int newScene);
	int getScene() const;
	void setBufferSize(int width, int height);
	sf::Sprite getSceneSprite();

};

#endif