#include "UIElement.hpp"

const float UIElement::PLAYER_PHOTO_SIZE = 180.f;
const float UIElement::HEALTH_BAR_WIDTH = 320.f;
const float UIElement::STATUS_ICON_SIZE = 60.f;

UIElement::UIElement(int type, Player* player)
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
		sprite.setPosition(sf::Vector2f(960.f - UIElement::PLAYER_PHOTO_SIZE - UIElement::STATUS_ICON_SIZE*2, 155.f));
		sprite.setTexture(texture);
		sprite.scale(UIElement::STATUS_ICON_SIZE / (float)sprite.getTexture()->getSize().x, UIElement::STATUS_ICON_SIZE / (float)sprite.getTexture()->getSize().y);
		break;

		case UIElement::TYPE_PLAYER_ONE_BULLET_BOOSTED:
		texture.loadFromFile("content/Image/UI/Battle/bullet_upgrade.png");
		texture2.loadFromFile("content/Image/UI/Battle/disable_bullet.png");
		sprite.setPosition(sf::Vector2f(UIElement::PLAYER_PHOTO_SIZE + UIElement::STATUS_ICON_SIZE*2 - 10.f, 155.f));
		sprite.setTexture(texture);
		sprite.scale((UIElement::STATUS_ICON_SIZE - 4.f) / (float)sprite.getTexture()->getSize().x, (UIElement::STATUS_ICON_SIZE - 4.f) / (float)sprite.getTexture()->getSize().y);
		break;

		case UIElement::TYPE_PLAYER_TWO_BULLET_BOOSTED:
		texture.loadFromFile("content/Image/UI/Battle/bullet_upgrade.png");
		texture2.loadFromFile("content/Image/UI/Battle/disable_bullet.png");
		sprite.setPosition(sf::Vector2f(974.f - UIElement::PLAYER_PHOTO_SIZE - UIElement::STATUS_ICON_SIZE*3, 155.f));
		sprite.setTexture(texture);
		sprite.scale((UIElement::STATUS_ICON_SIZE - 4.f) / (float)sprite.getTexture()->getSize().x, (UIElement::STATUS_ICON_SIZE - 4.f) / (float)sprite.getTexture()->getSize().y);
		break;

		default:
		break;
	}


}

UIElement::~UIElement()
{
}

void UIElement::update()
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

		default:
		break;
	}
}

void UIElement::draw(sf::RenderWindow& window) const
{
	window.draw(sprite);
}