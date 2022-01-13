#include "Box.hpp"
#include "Button.hpp"
#include "Map.hpp"
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




	void render();

	void __debug(const sf::Event& event);
};

#endif