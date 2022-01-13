#include "UIElement.hpp"

const float UIElement::PLAYER_PHOTO_SIZE = 180.f;
const float UIElement::HEALTH_BAR_WIDTH = 320.f;
const float UIElement::STATUS_ICON_SIZE = 60.f;

UIElement::UIElement(int type, Player* player) :
	rotationTimer(0.f)
{
	this->type = type;
	this->player = player;
	switch (type)
	{
		case UIElement::TYPE_PLAYER_ONE_PHOTO:
			texture.loadFromFile("content/Image/UI/Battle/headshot_blue.png");
			sprite.setPosition(sf::Vector2f(10.f, 10.f));
			sprite.setTexture(texture);
			sprite.scale(UIElement::PLAYER_PHOTO_SIZE / (float)sprite.getTexture()->getSize().x, UIElement::PLAYER_PHOTO_SIZE / (float)sprite.getTexture()->getSize().y);
			break;

		case UIElement::TYPE_PLAYER_TWO_PHOTO:
			texture.loadFromFile("content/Image/UI/Battle/headshot_red.png");
			sprite.setPosition(sf::Vector2f(950.f - UIElement::PLAYER_PHOTO_SIZE, 10.f));
			sprite.setTexture(texture);
			sprite.scale(UIElement::PLAYER_PHOTO_SIZE / (float)sprite.getTexture()->getSize().x, UIElement::PLAYER_PHOTO_SIZE / (float)sprite.getTexture()->getSize().y);
			break;

		case UIElement::TYPE_PLAYER_ONE_HEALTH_BAR_BG:
			texture.loadFromFile("content/Image/UI/Battle/health_bar_bg1.png");
			sprite.setPosition(sf::Vector2f(10.f, 220.f));
			sprite.setTexture(texture);
			sprite.scale(UIElement::HEALTH_BAR_WIDTH / (float)sprite.getTexture()->getSize().x, UIElement::HEALTH_BAR_WIDTH / (float)sprite.getTexture()->getSize().x);
			break;

		case UIElement::TYPE_PLAYER_TWO_HEALTH_BAR_BG:
			texture.loadFromFile("content/Image/UI/Battle/health_bar_bg2.png");
			sprite.setPosition(sf::Vector2f(950.f - UIElement::HEALTH_BAR_WIDTH, 220.f));
			sprite.setTexture(texture);
			sprite.scale(UIElement::HEALTH_BAR_WIDTH / (float)sprite.getTexture()->getSize().x, UIElement::HEALTH_BAR_WIDTH / (float)sprite.getTexture()->getSize().x);
			break;

		case UIElement::TYPE_PLAYER_ONE_HEALTH_BAR:
			texture.loadFromFile("content/Image/UI/Battle/health_bar1.png");
			sprite.setPosition(sf::Vector2f(10.f, 220.f));
			sprite.setTexture(texture);
			sprite.scale(UIElement::HEALTH_BAR_WIDTH / (float)sprite.getTexture()->getSize().x, UIElement::HEALTH_BAR_WIDTH / (float)sprite.getTexture()->getSize().x);
			break;

		case UIElement::TYPE_PLAYER_TWO_HEALTH_BAR:
			texture.loadFromFile("content/Image/UI/Battle/health_bar2.png");
			sprite.setPosition(sf::Vector2f(950.f, 220.f));
			sprite.setTexture(texture);
			sprite.setOrigin(sf::Vector2f(sprite.getTexture()->getSize().x, 0.f));
			sprite.scale(UIElement::HEALTH_BAR_WIDTH / (float)sprite.getTexture()->getSize().x, UIElement::HEALTH_BAR_WIDTH / (float)sprite.getTexture()->getSize().x);
			break;

		case UIElement::TYPE_PLAYER_ONE_HEALING:
			texture.loadFromFile("content/Image/UI/Battle/health_potion.png");
			texture2.loadFromFile("content/Image/UI/Battle/disable_heal.png");
			sprite.setPosition(sf::Vector2f(UIElement::PLAYER_PHOTO_SIZE + 10, 155.f));
			sprite.setTexture(texture);
			sprite.scale(UIElement::STATUS_ICON_SIZE / (float)sprite.getTexture()->getSize().x, UIElement::STATUS_ICON_SIZE / (float)sprite.getTexture()->getSize().y);
			break;

		case UIElement::TYPE_PLAYER_TWO_HEALING:
			texture.loadFromFile("content/Image/UI/Battle/health_potion.png");
			texture2.loadFromFile("content/Image/UI/Battle/disable_heal.png");
			sprite.setPosition(sf::Vector2f(950.f - UIElement::PLAYER_PHOTO_SIZE - UIElement::STATUS_ICON_SIZE, 155.f));
			sprite.setTexture(texture);
			sprite.scale(UIElement::STATUS_ICON_SIZE / (float)sprite.getTexture()->getSize().x, UIElement::STATUS_ICON_SIZE / (float)sprite.getTexture()->getSize().y);
			break;

		case UIElement::TYPE_PLAYER_ONE_SPEED_BOOSTED:
			texture.loadFromFile("content/Image/UI/Battle/speed_upgrade.png");
			texture2.loadFromFile("content/Image/UI/Battle/disable_speed.png");
			sprite.setPosition(sf::Vector2f(UIElement::PLAYER_PHOTO_SIZE + UIElement::STATUS_ICON_SIZE, 155.f));
			sprite.setTexture(texture);
			sprite.scale(UIElement::STATUS_ICON_SIZE / (float)sprite.getTexture()->getSize().x, UIElement::STATUS_ICON_SIZE / (float)sprite.getTexture()->getSize().y);
			break;

		case UIElement::TYPE_PLAYER_TWO_SPEED_BOOSTED:
			texture.loadFromFile("content/Image/UI/Battle/speed_upgrade.png");
			texture2.loadFromFile("content/Image/UI/Battle/disable_speed.png");
			sprite.setPosition(sf::Vector2f(960.f - UIElement::PLAYER_PHOTO_SIZE - UIElement::STATUS_ICON_SIZE * 2, 155.f));
			sprite.setTexture(texture);
			sprite.scale(UIElement::STATUS_ICON_SIZE / (float)sprite.getTexture()->getSize().x, UIElement::STATUS_ICON_SIZE / (float)sprite.getTexture()->getSize().y);
			break;

		case UIElement::TYPE_PLAYER_ONE_BULLET_BOOSTED:
			texture.loadFromFile("content/Image/UI/Battle/bullet_upgrade.png");
			texture2.loadFromFile("content/Image/UI/Battle/disable_bullet.png");
			sprite.setPosition(sf::Vector2f(UIElement::PLAYER_PHOTO_SIZE + UIElement::STATUS_ICON_SIZE * 2 - 10.f, 155.f));
			sprite.setTexture(texture);
			sprite.scale((UIElement::STATUS_ICON_SIZE - 4.f) / (float)sprite.getTexture()->getSize().x, (UIElement::STATUS_ICON_SIZE - 4.f) / (float)sprite.getTexture()->getSize().y);
			break;

		case UIElement::TYPE_PLAYER_TWO_BULLET_BOOSTED:
			texture.loadFromFile("content/Image/UI/Battle/bullet_upgrade.png");
			texture2.loadFromFile("content/Image/UI/Battle/disable_bullet.png");
			sprite.setPosition(sf::Vector2f(974.f - UIElement::PLAYER_PHOTO_SIZE - UIElement::STATUS_ICON_SIZE * 3, 155.f));
			sprite.setTexture(texture);
			sprite.scale((UIElement::STATUS_ICON_SIZE - 4.f) / (float)sprite.getTexture()->getSize().x, (UIElement::STATUS_ICON_SIZE - 4.f) / (float)sprite.getTexture()->getSize().y);
			break;

		case UIElement::TYPE_MAIN_MENU_BG:
			texture.loadFromFile("content/Image/UI/MainMenu/cover2.png");
			sprite.setPosition(sf::Vector2f(-200.f, 0.f));
			sprite.setTexture(texture);
			sprite.scale(960.f / (float)sprite.getTexture()->getSize().y, 960.f / (float)sprite.getTexture()->getSize().y);
			break;

		case UIElement::TYPE_BLUE_BODY_COVER:
			texture.loadFromFile("content/Image/UI/MainMenu/cover_blue_body.png");
			sprite.setPosition(sf::Vector2f(-150.f, 370.f));
			sprite.setTexture(texture);
			sprite.scale(250.f / (float)sprite.getTexture()->getSize().y, 250.f / (float)sprite.getTexture()->getSize().y);
			break;

		case UIElement::TYPE_RED_BODY_COVER:
			texture.loadFromFile("content/Image/UI/MainMenu/cover_red_body.png");
			sprite.setPosition(sf::Vector2f(600.f, 370.f));
			sprite.setTexture(texture);
			sprite.scale(250.f / (float)sprite.getTexture()->getSize().y, 250.f / (float)sprite.getTexture()->getSize().y);
			break;

		case UIElement::TYPE_BLUE_BARREL_COVER:
			texture.loadFromFile("content/Image/UI/MainMenu/cover_blue_barrel.png");
			sprite.setPosition(sf::Vector2f(190.f, 405.f));
			sprite.setTexture(texture);
			sprite.scale(72.f / (float)sprite.getTexture()->getSize().y, 72.f / (float)sprite.getTexture()->getSize().y);
			sprite.rotate(5.f);
			isRotatingClockwise = true;
			break;

		case UIElement::TYPE_RED_BARREL_COVER:
			texture.loadFromFile("content/Image/UI/MainMenu/cover_red_barrel.png");
			sprite.setPosition(sf::Vector2f(758.f, 413.f));
			sprite.setTexture(texture);
			sprite.scale(41.f / (float)sprite.getTexture()->getSize().y, 41.f / (float)sprite.getTexture()->getSize().y);
			sprite.setOrigin(sf::Vector2f(sprite.getTexture()->getSize().x, 0.f));
			sprite.rotate(-5.f);
			isRotatingClockwise = false;
			break;

		case UIElement::TYPE_MAIN_MENU_TITLE:
			texture.loadFromFile("content/Image/UI/MainMenu/title.png");
			sprite.setPosition(sf::Vector2f(480.f, 160.f));
			sprite.setTexture(texture);
			sprite.scale(165.f / (float)sprite.getTexture()->getSize().y, 165.f / (float)sprite.getTexture()->getSize().y);
			sprite.setOrigin(sf::Vector2f(sprite.getTexture()->getSize().x / 2.f, sprite.getTexture()->getSize().y / 2.f));
			isRotatingClockwise = false;
			break;

		case UIElement::TYPE_HOW_TO_PLAY_INSTRUCTIONS:
			texture.loadFromFile("content/Image/UI/HowToPlay/instructions.png");
			sprite.setPosition(sf::Vector2f(0.f, 0.f));
			sprite.setTexture(texture);
			sprite.scale(960.f / (float)sprite.getTexture()->getSize().x, 960.f / (float)sprite.getTexture()->getSize().y);
			break;

		case UIElement::TYPE_WIN_PLAYER_ONE_PHOTO:
			texture.loadFromFile("content/Image/UI/Win/headshot_blue.png");
			sprite.setPosition(sf::Vector2f(480.f, 550.f));
			sprite.setTexture(texture);
			sprite.scale(400.f / (float)sprite.getTexture()->getSize().x, 400.f / (float)sprite.getTexture()->getSize().y);
			sprite.setOrigin(sf::Vector2f(sprite.getTexture()->getSize().x / 2.f, sprite.getTexture()->getSize().y / 2.f));
			break;

		case UIElement::TYPE_WIN_PLAYER_TWO_PHOTO:
			texture.loadFromFile("content/Image/UI/Win/headshot_red.png");
			sprite.setPosition(sf::Vector2f(480.f, 550.f));
			sprite.setTexture(texture);
			sprite.scale(400.f / (float)sprite.getTexture()->getSize().x, 400.f / (float)sprite.getTexture()->getSize().y);
			sprite.setOrigin(sf::Vector2f(sprite.getTexture()->getSize().x / 2.f, sprite.getTexture()->getSize().y / 2.f));
			break;

		case UIElement::TYPE_WIN_TEXT:
			texture.loadFromFile("content/Image/UI/Win/winner_text.png");
			sprite.setPosition(sf::Vector2f(480.f, 220.f));
			sprite.setTexture(texture);
			sprite.scale(260.f / (float)sprite.getTexture()->getSize().y, 260.f / (float)sprite.getTexture()->getSize().y);
			sprite.setOrigin(sf::Vector2f(sprite.getTexture()->getSize().x / 2.f, sprite.getTexture()->getSize().y / 2.f));
			break;

		case UIElement::TYPE_VICTORY_TEXT:
			texture.loadFromFile("content/Image/UI/Victory/victory_text.png");
			sprite.setPosition(sf::Vector2f(480.f, 220.f));
			sprite.setTexture(texture);
			sprite.scale(240.f / (float)sprite.getTexture()->getSize().y, 240.f / (float)sprite.getTexture()->getSize().y);
			sprite.setOrigin(sf::Vector2f(sprite.getTexture()->getSize().x / 2.f, sprite.getTexture()->getSize().y / 2.f));

		default:
			break;
	}
}

UIElement::~UIElement()
{
}

void UIElement::update(float deltaTime)
{
	switch (type)
	{
		case UIElement::TYPE_PLAYER_ONE_HEALTH_BAR:
		case UIElement::TYPE_PLAYER_TWO_HEALTH_BAR:
			sprite.setScale(UIElement::HEALTH_BAR_WIDTH / (float)sprite.getTexture()->getSize().x, UIElement::HEALTH_BAR_WIDTH / (float)sprite.getTexture()->getSize().x);
			sprite.scale(player->getHp() / 100.f, 1);
			break;

		case UIElement::TYPE_PLAYER_ONE_HEALING:
		case UIElement::TYPE_PLAYER_TWO_HEALING:
			if (player->status.isHealing())
				sprite.setTexture(texture);
			else
				sprite.setTexture(texture2);
			break;

		case UIElement::TYPE_PLAYER_ONE_SPEED_BOOSTED:
		case UIElement::TYPE_PLAYER_TWO_SPEED_BOOSTED:
			if (player->status.isSpeedBoosted())
				sprite.setTexture(texture);
			else
				sprite.setTexture(texture2);
			break;

		case UIElement::TYPE_PLAYER_ONE_BULLET_BOOSTED:
		case UIElement::TYPE_PLAYER_TWO_BULLET_BOOSTED:
			if (player->status.isBulletBoosted())
				sprite.setTexture(texture);
			else
				sprite.setTexture(texture2);
			break;

		case UIElement::TYPE_BLUE_BARREL_COVER:
		case UIElement::TYPE_RED_BARREL_COVER:
			rotationTimer += deltaTime;
			if (rotationTimer >= 3.f)
			{
				isRotatingClockwise = !isRotatingClockwise;
				rotationTimer = 0.f;
			}
			if (isRotatingClockwise)
				sprite.rotate(deltaTime * UIElement::BARREL_OMEGA);
			else
				sprite.rotate(-deltaTime * UIElement::BARREL_OMEGA);
			break;

		default:
			break;
	}
}

void UIElement::draw(sf::RenderWindow& window) const
{
	window.draw(sprite);
}

void UIElement::draw(sf::RenderTexture& buffer) const
{
	buffer.draw(sprite);
}