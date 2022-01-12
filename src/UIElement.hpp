#include "Platform/Platform.hpp"
#include "Player.hpp"

#ifndef UIELEMENT_HPP
#define UIELEMENT_HPP

class UIElement {
private:
	static const float PLAYER_PHOTO_SIZE;
	static const float HEALTH_BAR_WIDTH;
	static const float STATUS_ICON_SIZE;

	sf::Texture texture;
	sf::Texture texture2;
	sf::Sprite sprite;
	Player* player;
	int type;
public:
	static const int TYPE_PLAYER_ONE_PHOTO = 0;
	static const int TYPE_PLAYER_TWO_PHOTO = 1;
	static const int TYPE_PLAYER_ONE_HEALTH_BAR = 2;
	static const int TYPE_PLAYER_TWO_HEALTH_BAR = 3;
	static const int TYPE_PLAYER_ONE_HEALTH_BAR_BG = 4;
	static const int TYPE_PLAYER_TWO_HEALTH_BAR_BG = 5;
	static const int TYPE_PLAYER_ONE_HEALING = 6;
	static const int TYPE_PLAYER_TWO_HEALING = 7;
	static const int TYPE_PLAYER_ONE_SPEED_BOOSTED = 8;
	static const int TYPE_PLAYER_TWO_SPEED_BOOSTED = 9;
	static const int TYPE_PLAYER_ONE_BULLET_BOOSTED = 10;
	static const int TYPE_PLAYER_TWO_BULLET_BOOSTED = 11;

	UIElement(int type, Player* player);
	~UIElement();

	void update();
	void draw(sf::RenderWindow& window) const;
};

#endif