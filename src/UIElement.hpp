#include "Platform/Platform.hpp"
#include "Player.hpp"

#ifndef UIELEMENT_HPP
#define UIELEMENT_HPP

class UIElement {
private:

	std::vector<sf::Texture> textures;
	sf::Sprite sprite;
	Player* player;
	int* target;
	int type;
	bool isRotatingClockwise;
	float rotationTimer;

	void init(const sf::Vector2f& pos);

public:
	static const float PLAYER_PHOTO_SIZE;
	static const float HEALTH_BAR_WIDTH;
	static const float STATUS_ICON_SIZE;
	static const float PLAYER_WIN_LIGHT_SIZE;
	static const float MAP_PREVIEW_SIZE;
	static const float MINIMAP_ARROW_SIZE;
	static const int BARREL_OMEGA = 3;
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
	static const int TYPE_PLAYER_WIN_LIGHT_ONE = 23;
	static const int TYPE_PLAYER_WIN_LIGHT_TWO = 24;
	static const int TYPE_PLAYER_WIN_LIGHT_THREE = 25;
	static const int TYPE_PAUSE_TEXT = 26;
	static const int TYPE_CHOOSE_MAP_PREVIEW = 27;
	static const int TYPE_PLAYER_ONE_ARROW = 28;
	static const int TYPE_PLAYER_TWO_ARROW = 29;
	static const int TYPE_CHOOSE_MAP_TEXT = 30;

	UIElement(int type, Player* player, const sf::Vector2f& pos);
	UIElement(int type, int* target, const sf::Vector2f& pos);
	UIElement(int type, const sf::Vector2f& pos);
	~UIElement();

	void update(float deltaTime);
	void draw(sf::RenderWindow& window) const;
	void draw(sf::RenderTexture& buffer) const;
};

#endif