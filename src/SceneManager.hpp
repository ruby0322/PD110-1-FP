#include "Platform/Platform.hpp"
#include "Player.hpp"
#include "Entity.hpp"
#include "Item.hpp"
#include "Projectile.hpp"
#include "Map.hpp"
#include "MapManager.hpp"
#include "UIElement.hpp"

#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

class SceneManager {
private:

	int currScene;
	sf::RenderTexture sceneBuffer;

	sf::View playerOneView;
	sf::View playerTwoView;
	sf::View miniMap;

	void renderSceneBuffer();
	void updateBattle(float deltaTime);
	void updateMainMenu(float deltaTime);
	void handleEventBattle(const sf::Event& event);
	void handleEventMainMenu(const sf::Event& event);
	void clearDeadProjectiles();
	void clearDeadItems();
	sf::Vector2f fixCameraCenter(const sf::Vector2f& pos);
	void updateCameras();


public:

	static const int SCENE_MAIN_MENU = 0;
	static const int SCENE_HOW_TO_PLAY = 1;
	static const int SCENE_CHOOSE_MAP = 2;
	static const int SCENE_BATTLE = 3;
	static const int SCENE_PAUSE = 4;
	static const int SCENE_WIN = 5;
	static const int SCENE_VICTORY = 6;
	static const int SCENE_QUIT = 7;
	static const int SCENE_END = 8;

	std::vector<Entity*> mainMenuEntities;

	std::vector<Player*> players;
	std::vector<Entity*> entities;
	std::vector<Item*> items;
	std::vector<Projectile*> projectiles;
	std::vector<sf::Text*> texts;
	std::vector<UIElement*> uiElements;

	Map map;

	SceneManager();
	~SceneManager();

	void init(float windowWidth, float windowHeight);
	void handleEvent(const sf::Event& event);
	void newRound(int mapNumber);
	void update(float deltaTime);
	void setScene(int newScene);
	int getScene() const;
	void renderWindow(sf::RenderWindow& window);
	sf::Sprite getSceneSprite();

};

#endif