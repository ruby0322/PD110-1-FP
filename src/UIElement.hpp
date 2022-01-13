#include "Platform/Platform.hpp"
#include "Player.hpp"

#ifndef UIELEMENT_HPP
#define UIELEMENT_HPP

class UIElement {
private:
	static const float PLAYER_PHOTO_SIZE;
	static const float HEALTH_BAR_WIDTH;
	static const float STATUS_ICON_SIZE;
	static const int BARREL_OMEGA = 3;

	sf::Texture texture;
	sf::Texture texture2;
	sf::Sprite sprite;
	Player* player;
	int type;
	bool isRotatingClockwise;
	float rotationTimer;

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
	static const int TYPE_MAIN_MENU_BG = 12;
	static const int TYPE_BLUE_BODY_COVER = 13;
	static const int TYPE_RED_BODY_COVER = 14;
	static const int TYPE_BLUE_BARREL_COVER = 15;
	static const int TYPE_RED_BARREL_COVER = 16;
	static const int TYPE_MAIN_MENU_TITLE = 17;
	static const int TYPE_HOW_TO_PLAY_INSTRUCTIONS = 18;
	static const int TYPE_WIN_PLAYER_ONE_PHOTO = 19;
	static const int TYPE_WIN_PLAYER_TWO_PHOTO = 20;
	static const int TYPE_WIN_TEXT = 21;
	static const int TYPE_VICTORY_TEXT = 22;

	UIElement(int type, Player* player);
	~UIElement();

	void update(float deltaTime);
	void draw(sf::RenderWindow& window) const;
	void draw(sf::RenderTexture& buffer) const;
};

#endif