#include "Entity.hpp"
#include "SoundManager.hpp"

#ifndef BUTTON_HPP
	#define BUTTON_HPP

class Button : public Entity
{
private:
	static const int BUTTON_HEIGHT = 120;
	int* target;
	int* event;

	int type;
	bool clicked;
	bool isPointInside(const sf::Vector2f& pos) const;
	void trigger();

public:
	static const int TYPE_PLAY = 0;
	static const int TYPE_PAUSE = 1;
	static const int TYPE_INFO = 2;
	static const int TYPE_QUIT = 3;
	static const int TYPE_MAIN_MENU = 4;
	static const int TYPE_HOW_TO_PLAY_BACK = 5;
	static const int TYPE_PAUSE_BACK = 7;
	static const int TYPE_PAUSE_RESET = 8;
	static const int TYPE_VICTORY_RESET = 9;

	static const int EVENT_NONE = 0;
	static const int EVENT_NEW_ROUND = 1;
	static const int EVENT_NEW_GAME = 2;

	Button(int type, int* target, int* event, const sf::Vector2f& pos);
	~Button();
	void handleEvent(const sf::Event& event) override;
	void update(float deltaTime) override;
};

#endif