#include "Player.hpp"
#include "Item.hpp"
#include "Projectile.hpp"
#include "MapManager.hpp"
#include "UIElement.hpp"
#include "Button.hpp"

#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

class SceneManager {
private:

	int currScene;
	sf::RenderTexture sceneBuffer;

	sf::View playerOneView;
	sf::View playerTwoView;
	sf::View miniMap;

	int winnerOfTheRound;

	std::vector<Player*> players;
	std::vector<Item*> items;
	std::vector<Projectile*> projectiles;

	std::vector<UIElement*> battleUiElements;
	std::vector<UIElement*> mainMenuUiElements;
	std::vector<UIElement*> howToPlayUiElements;
	std::vector<UIElement*> pauseUiElements;
	std::vector<UIElement*> winUiElements;
	std::vector<UIElement*> victoryUiElements;
	std::vector<UIElement*> chooseMapUiElements;
	std::vector<UIElement*> miniMapUiElements;

	std::vector<Button*> mainMenuButtons;
	std::vector<Button*> howToPlayButtons;
	std::vector<Button*> pauseButtons;
	std::vector<Button*> winButtons;
	std::vector<Button*> victoryButtons;
	std::vector<Button*> chooseMapButtons;

	Map map;

	void renderSceneBuffer();
	void updateBattle(float deltaTime);
	void updateMainMenu(float deltaTime);
	void updateChooseMap(float deltaTime);
	void handleEventBattle(const sf::Event& event);
	void handleEventMainMenu(const sf::Event& event);
	void handleEventHowToPlay(const sf::Event& event);
	void handleEventPause(const sf::Event& event);
	void handleEventWin(const sf::Event& event);
	void handleEventVictory(const sf::Event& event);
	void handleEventChooseMap(const sf::Event& event);

	void handleButtonEvent();
	void clearDeadProjectiles();
	void clearDeadItems();
	sf::Vector2f fixCameraCenter(const sf::Vector2f& pos);
	void updateCameras();

	void clearItems();
	void clearProjectiles();
	void clearPlayers();

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

	int currMap;
	int buttonEvent;


	SceneManager();
	~SceneManager();

	void init(float windowWidth, float windowHeight);
	void handleEvent(const sf::Event& event);
	void newRound(int mapNumber);
	void update(float deltaTime);
	void setScene(int newScene);
	int& getScene();
	void renderWindow(sf::RenderWindow& window);
	sf::Sprite getSceneSprite();

};

#endif