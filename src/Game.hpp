#include "Box.hpp"
#include "Button.hpp"
#include "Entity.hpp"
#include "Map.hpp"
#include "Platform/Platform.hpp"
#include "Player.hpp"
#include "SceneManager.hpp"
#include "SoundManager.hpp"

#ifndef GAME_HPP
	#define GAME_HPP

class Game
{
public:
	void run();
	void init(float, float, const char*);

	Game();
	~Game();

private:
	util::Platform platform;
	sf::RenderWindow window;

	sf::Clock clock;

	SceneManager sceneManager;

	sf::View playerOneView;
	sf::View playerTwoView;
	sf::View miniMap;

	sf::Vector2f fixCameraCenter(const sf::Vector2f& pos);
	void render();
	void updateCameras();

	void __debug(const sf::Event& event);
};

#endif