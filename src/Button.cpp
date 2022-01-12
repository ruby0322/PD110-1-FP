#include "Button.hpp"

Button::Button(const std::vector<sf::Texture>& frames, int type, SceneManager* target) :
	Entity(frames),
	target(target)
{
	this->clicked = false;
	this->type = type;
}

Button::~Button()
{
}

bool Button::isPointInside(const sf::Vector2f& pos) const
{

	return sprite.getGlobalBounds().contains(pos);
}

void Button::trigger() {
	switch (type) {
		case Button::TYPE_PLAY:
		target->setScene(SceneManager::SCENE_BATTLE);
		break;
		case Button::TYPE_PAUSE:
		target->setScene(SceneManager::SCENE_PAUSE);
		break;
		case Button::TYPE_INFO:
		target->setScene(SceneManager::SCENE_HOW_TO_PLAY);
		break;
		case Button::TYPE_QUIT:
		target->setScene(SceneManager::SCENE_QUIT);
		break;
		case Button::TYPE_MAIN_MENU:
		target->setScene(SceneManager::SCENE_MAIN_MENU);
		break;
		default:
		break;
	}
}

void Button::handleEvent(const sf::Event& event) {
	switch (event.type)
	{
		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left) {
				if (isPointInside(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
				{
					clicked = true;
					setFrame(1);
				}
			}
			break;
		case sf::Event::MouseButtonReleased:
			if (event.mouseButton.button == sf::Mouse::Left) {
				if (isPointInside(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
				{
					if (clicked) {
						trigger();
						setFrame(0);
					}
				}
				clicked = false;
			}
			break;
		default:
			break;
	}
}

void Button::update(float deltaTime)
{
	updateTimer += deltaTime;
	if (updateTimer >= Entity::UPDATE_TIME)
	{
		updateTimer -= Entity::UPDATE_TIME;
	}
}