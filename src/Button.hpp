#include "Platform/Platform.hpp"
#include "SceneManager.hpp"

#ifndef BUTTON_HPP
	#define BUTTON_HPP

class Button : public Entity
{
private:
	SceneManager* target;

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

	Button(const std::vector<sf::Texture>& frames, int type, SceneManager* target);
	~Button();
	void handleEvent(const sf::Event& event) override;
	void update(float deltaTime) override;
};

#endif