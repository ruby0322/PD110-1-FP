#include "UIElement.hpp"

const float UIElement::PLAYER_PHOTO_SIZE = 180.f;
const float UIElement::HEALTH_BAR_WIDTH = 320.f;
const float UIElement::STATUS_ICON_SIZE = 60.f;
const float UIElement::PLAYER_WIN_LIGHT_SIZE = 36.f;
const float UIElement::MAP_PREVIEW_SIZE = 700.f;
const float UIElement::MINIMAP_ARROW_SIZE = 150.f;

UIElement::UIElement(int type, Player* player, const sf::Vector2f& pos) :
	rotationTimer(0.f)
{
	this->type = type;
	this->player = player;
	init(pos);
}

UIElement::UIElement(int type, const sf::Vector2f& pos) :
	rotationTimer(0.f)
{
	this->type = type;
	init(pos);
}
UIElement::UIElement(int type, int* target, const sf::Vector2f& pos) :
	rotationTimer(0.f)
{
	this->type = type;
	this->target = target;
	init(pos);
}

UIElement::~UIElement()
{
}

void UIElement::init(const sf::Vector2f& pos)
{
	sf::Texture texture;
	switch (type)
	{
		case UIElement::TYPE_PLAYER_ONE_PHOTO:
			texture.loadFromFile("content/Image/UI/Battle/headshot_blue.png");
			sprite.setPosition(sf::Vector2f(10.f, 10.f));
			textures.push_back(texture);
			sprite.setTexture(textures[0]);
			sprite.scale(UIElement::PLAYER_PHOTO_SIZE / (float)sprite.getTexture()->getSize().x, UIElement::PLAYER_PHOTO_SIZE / (float)sprite.getTexture()->getSize().y);
			break;

		case UIElement::TYPE_PLAYER_TWO_PHOTO:
			texture.loadFromFile("content/Image/UI/Battle/headshot_red.png");
			sprite.setPosition(sf::Vector2f(950.f - UIElement::PLAYER_PHOTO_SIZE, 10.f));
			textures.push_back(texture);
			sprite.setTexture(textures[0]);
			sprite.scale(UIElement::PLAYER_PHOTO_SIZE / (float)sprite.getTexture()->getSize().x, UIElement::PLAYER_PHOTO_SIZE / (float)sprite.getTexture()->getSize().y);
			break;

		case UIElement::TYPE_PLAYER_ONE_HEALTH_BAR_BG:
			texture.loadFromFile("content/Image/UI/Battle/health_bar_bg1.png");
			sprite.setPosition(sf::Vector2f(10.f, 220.f));
			textures.push_back(texture);
			sprite.setTexture(textures[0]);
			sprite.scale(UIElement::HEALTH_BAR_WIDTH / (float)sprite.getTexture()->getSize().x, UIElement::HEALTH_BAR_WIDTH / (float)sprite.getTexture()->getSize().x);
			break;

		case UIElement::TYPE_PLAYER_TWO_HEALTH_BAR_BG:
			texture.loadFromFile("content/Image/UI/Battle/health_bar_bg2.png");
			sprite.setPosition(sf::Vector2f(950.f - UIElement::HEALTH_BAR_WIDTH, 220.f));
			textures.push_back(texture);
			sprite.setTexture(textures[0]);
			sprite.scale(UIElement::HEALTH_BAR_WIDTH / (float)sprite.getTexture()->getSize().x, UIElement::HEALTH_BAR_WIDTH / (float)sprite.getTexture()->getSize().x);
			break;

		case UIElement::TYPE_PLAYER_ONE_HEALTH_BAR:
			texture.loadFromFile("content/Image/UI/Battle/health_bar1.png");
			sprite.setPosition(sf::Vector2f(10.f, 220.f));
			textures.push_back(texture);
			sprite.setTexture(textures[0]);
			sprite.scale(UIElement::HEALTH_BAR_WIDTH / (float)sprite.getTexture()->getSize().x, UIElement::HEALTH_BAR_WIDTH / (float)sprite.getTexture()->getSize().x);
			break;

		case UIElement::TYPE_PLAYER_TWO_HEALTH_BAR:
			texture.loadFromFile("content/Image/UI/Battle/health_bar2.png");
			sprite.setPosition(sf::Vector2f(950.f, 220.f));
			textures.push_back(texture);
			sprite.setTexture(textures[0]);
			sprite.setOrigin(sf::Vector2f(sprite.getTexture()->getSize().x, 0.f));
			sprite.scale(UIElement::HEALTH_BAR_WIDTH / (float)sprite.getTexture()->getSize().x, UIElement::HEALTH_BAR_WIDTH / (float)sprite.getTexture()->getSize().x);
			break;

		case UIElement::TYPE_PLAYER_ONE_HEALING:
			texture.loadFromFile("content/Image/UI/Battle/health_potion.png");
			textures.push_back(texture);
			texture.loadFromFile("content/Image/UI/Battle/disable_heal.png");
			textures.push_back(texture);
			sprite.setPosition(sf::Vector2f(UIElement::PLAYER_PHOTO_SIZE + 10, 155.f));
			sprite.setTexture(textures[0]);
			sprite.scale(UIElement::STATUS_ICON_SIZE / (float)sprite.getTexture()->getSize().x, UIElement::STATUS_ICON_SIZE / (float)sprite.getTexture()->getSize().y);
			break;

		case UIElement::TYPE_PLAYER_TWO_HEALING:
			texture.loadFromFile("content/Image/UI/Battle/health_potion.png");
			textures.push_back(texture);
			texture.loadFromFile("content/Image/UI/Battle/disable_heal.png");
			textures.push_back(texture);
			sprite.setPosition(sf::Vector2f(950.f - UIElement::PLAYER_PHOTO_SIZE - UIElement::STATUS_ICON_SIZE, 155.f));
			sprite.setTexture(textures[0]);
			sprite.scale(UIElement::STATUS_ICON_SIZE / (float)sprite.getTexture()->getSize().x, UIElement::STATUS_ICON_SIZE / (float)sprite.getTexture()->getSize().y);
			break;

		case UIElement::TYPE_PLAYER_ONE_SPEED_BOOSTED:
			texture.loadFromFile("content/Image/UI/Battle/speed_upgrade.png");
			textures.push_back(texture);
			texture.loadFromFile("content/Image/UI/Battle/disable_speed.png");
			textures.push_back(texture);
			sprite.setPosition(sf::Vector2f(UIElement::PLAYER_PHOTO_SIZE + UIElement::STATUS_ICON_SIZE, 155.f));
			sprite.setTexture(textures[0]);
			sprite.scale(UIElement::STATUS_ICON_SIZE / (float)sprite.getTexture()->getSize().x, UIElement::STATUS_ICON_SIZE / (float)sprite.getTexture()->getSize().y);
			break;

		case UIElement::TYPE_PLAYER_TWO_SPEED_BOOSTED:
			texture.loadFromFile("content/Image/UI/Battle/speed_upgrade.png");
			textures.push_back(texture);
			texture.loadFromFile("content/Image/UI/Battle/disable_speed.png");
			textures.push_back(texture);
			sprite.setPosition(sf::Vector2f(960.f - UIElement::PLAYER_PHOTO_SIZE - UIElement::STATUS_ICON_SIZE * 2, 155.f));
			sprite.setTexture(textures[0]);
			sprite.scale(UIElement::STATUS_ICON_SIZE / (float)sprite.getTexture()->getSize().x, UIElement::STATUS_ICON_SIZE / (float)sprite.getTexture()->getSize().y);
			break;

		case UIElement::TYPE_PLAYER_ONE_BULLET_BOOSTED:
			texture.loadFromFile("content/Image/UI/Battle/bullet_upgrade.png");
			textures.push_back(texture);
			texture.loadFromFile("content/Image/UI/Battle/disable_bullet.png");
			textures.push_back(texture);
			sprite.setPosition(sf::Vector2f(UIElement::PLAYER_PHOTO_SIZE + UIElement::STATUS_ICON_SIZE * 2 - 10.f, 155.f));
			sprite.setTexture(textures[0]);
			sprite.scale((UIElement::STATUS_ICON_SIZE - 4.f) / (float)sprite.getTexture()->getSize().x, (UIElement::STATUS_ICON_SIZE - 4.f) / (float)sprite.getTexture()->getSize().y);
			break;

		case UIElement::TYPE_PLAYER_TWO_BULLET_BOOSTED:
			texture.loadFromFile("content/Image/UI/Battle/bullet_upgrade.png");
			textures.push_back(texture);
			texture.loadFromFile("content/Image/UI/Battle/disable_bullet.png");
			textures.push_back(texture);
			sprite.setTexture(textures[0]);
			sprite.setPosition(sf::Vector2f(974.f - UIElement::PLAYER_PHOTO_SIZE - UIElement::STATUS_ICON_SIZE * 3, 155.f));
			sprite.scale((UIElement::STATUS_ICON_SIZE - 4.f) / (float)sprite.getTexture()->getSize().x, (UIElement::STATUS_ICON_SIZE - 4.f) / (float)sprite.getTexture()->getSize().y);
			break;

		case UIElement::TYPE_MAIN_MENU_BG:
			texture.loadFromFile("content/Image/UI/MainMenu/cover2.png");
			sprite.setPosition(sf::Vector2f(-200.f, 0.f));
			textures.push_back(texture);
			sprite.setTexture(textures[0]);
			sprite.scale(960.f / (float)sprite.getTexture()->getSize().y, 960.f / (float)sprite.getTexture()->getSize().y);
			break;

		case UIElement::TYPE_BLUE_BODY_COVER:
			texture.loadFromFile("content/Image/UI/MainMenu/cover_blue_body.png");
			sprite.setPosition(sf::Vector2f(-150.f, 370.f));
			textures.push_back(texture);
			sprite.setTexture(textures[0]);
			sprite.scale(250.f / (float)sprite.getTexture()->getSize().y, 250.f / (float)sprite.getTexture()->getSize().y);
			break;

		case UIElement::TYPE_RED_BODY_COVER:
			texture.loadFromFile("content/Image/UI/MainMenu/cover_red_body.png");
			sprite.setPosition(sf::Vector2f(600.f, 370.f));
			textures.push_back(texture);
			sprite.setTexture(textures[0]);
			sprite.scale(250.f / (float)sprite.getTexture()->getSize().y, 250.f / (float)sprite.getTexture()->getSize().y);
			break;

		case UIElement::TYPE_BLUE_BARREL_COVER:
			texture.loadFromFile("content/Image/UI/MainMenu/cover_blue_barrel.png");
			sprite.setPosition(sf::Vector2f(192.f, 410.f));
			textures.push_back(texture);
			sprite.setTexture(textures[0]);
			sprite.scale(72.f / (float)sprite.getTexture()->getSize().y, 72.f / (float)sprite.getTexture()->getSize().y);
			sprite.rotate(15.f);
			isRotatingClockwise = true;
			break;

		case UIElement::TYPE_RED_BARREL_COVER:
			texture.loadFromFile("content/Image/UI/MainMenu/cover_red_barrel.png");
			sprite.setPosition(sf::Vector2f(758.f, 413.f));
			textures.push_back(texture);
			sprite.setTexture(textures[0]);
			sprite.scale(41.f / (float)sprite.getTexture()->getSize().y, 41.f / (float)sprite.getTexture()->getSize().y);
			sprite.setOrigin(sf::Vector2f(sprite.getTexture()->getSize().x, 0.f));
			sprite.rotate(-15.f);
			isRotatingClockwise = false;
			break;

		case UIElement::TYPE_MAIN_MENU_TITLE:
			texture.loadFromFile("content/Image/UI/MainMenu/title.png");
			sprite.setPosition(sf::Vector2f(480.f, 160.f));
			textures.push_back(texture);
			sprite.setTexture(textures[0]);
			sprite.scale(165.f / (float)sprite.getTexture()->getSize().y, 165.f / (float)sprite.getTexture()->getSize().y);
			sprite.setOrigin(sf::Vector2f(sprite.getTexture()->getSize().x / 2.f, sprite.getTexture()->getSize().y / 2.f));
			isRotatingClockwise = false;
			break;

		case UIElement::TYPE_HOW_TO_PLAY_INSTRUCTIONS:
			texture.loadFromFile("content/Image/UI/HowToPlay/instructions.png");
			sprite.setPosition(sf::Vector2f(0.f, 0.f));
			textures.push_back(texture);
			sprite.setTexture(textures[0]);
			sprite.scale(960.f / (float)sprite.getTexture()->getSize().x, 960.f / (float)sprite.getTexture()->getSize().y);
			break;

		case UIElement::TYPE_WIN_PLAYER_ONE_PHOTO:
			texture.loadFromFile("content/Image/UI/Win/headshot_blue.png");
			sprite.setPosition(sf::Vector2f(480.f, 550.f));
			textures.push_back(texture);
			sprite.setTexture(textures[0]);
			sprite.scale(400.f / (float)sprite.getTexture()->getSize().x, 400.f / (float)sprite.getTexture()->getSize().y);
			sprite.setOrigin(sf::Vector2f(sprite.getTexture()->getSize().x / 2.f, sprite.getTexture()->getSize().y / 2.f));
			break;

		case UIElement::TYPE_WIN_PLAYER_TWO_PHOTO:
			texture.loadFromFile("content/Image/UI/Win/headshot_red.png");
			sprite.setPosition(sf::Vector2f(480.f, 550.f));
			textures.push_back(texture);
			sprite.setTexture(textures[0]);
			sprite.scale(400.f / (float)sprite.getTexture()->getSize().x, 400.f / (float)sprite.getTexture()->getSize().y);
			sprite.setOrigin(sf::Vector2f(sprite.getTexture()->getSize().x / 2.f, sprite.getTexture()->getSize().y / 2.f));
			break;

		case UIElement::TYPE_WIN_TEXT:
			texture.loadFromFile("content/Image/UI/Win/winner_text.png");
			sprite.setPosition(sf::Vector2f(480.f, 220.f));
			textures.push_back(texture);
			sprite.setTexture(textures[0]);
			sprite.scale(260.f / (float)sprite.getTexture()->getSize().y, 260.f / (float)sprite.getTexture()->getSize().y);
			sprite.setOrigin(sf::Vector2f(sprite.getTexture()->getSize().x / 2.f, sprite.getTexture()->getSize().y / 2.f));
			break;

		case UIElement::TYPE_VICTORY_TEXT:
			texture.loadFromFile("content/Image/UI/Victory/victory_text.png");
			sprite.setPosition(sf::Vector2f(480.f, 220.f));
			textures.push_back(texture);
			sprite.setTexture(textures[0]);
			sprite.scale(240.f / (float)sprite.getTexture()->getSize().y, 240.f / (float)sprite.getTexture()->getSize().y);
			sprite.setOrigin(sf::Vector2f(sprite.getTexture()->getSize().x / 2.f, sprite.getTexture()->getSize().y / 2.f));
			break;

		case UIElement::TYPE_PLAYER_WIN_LIGHT_ONE:
		case UIElement::TYPE_PLAYER_WIN_LIGHT_TWO:
		case UIElement::TYPE_PLAYER_WIN_LIGHT_THREE:
			texture.loadFromFile("content/Image/UI/Battle/grey_dot.png");
			textures.push_back(texture);
			texture.loadFromFile("content/Image/UI/Battle/orange_dot.png");
			textures.push_back(texture);
			sprite.setTexture(textures[0]);
			sprite.scale(UIElement::PLAYER_WIN_LIGHT_SIZE / (float)sprite.getTexture()->getSize().x, UIElement::PLAYER_WIN_LIGHT_SIZE / (float)sprite.getTexture()->getSize().y);
			sprite.setOrigin(sf::Vector2f(sprite.getTexture()->getSize().x / 2.f, sprite.getTexture()->getSize().y / 2.f));
			sprite.setPosition(pos);
			break;

		case UIElement::TYPE_PAUSE_TEXT:
			texture.loadFromFile("content/Image/UI/Pause/pause_text.png");
			textures.push_back(texture);
			sprite.setTexture(textures[0]);
			sprite.scale(220.f / (float)sprite.getTexture()->getSize().y, 220.f / (float)sprite.getTexture()->getSize().y);
			sprite.setOrigin(sf::Vector2f(sprite.getTexture()->getSize().x / 2.f, sprite.getTexture()->getSize().y / 2.f));
			sprite.setPosition(pos);
			break;

		case UIElement::TYPE_CHOOSE_MAP_PREVIEW:
			for (int i = 1; i <= 9; ++i)
			{
				texture.loadFromFile("content/Image/UI/ChooseMap/" + std::to_string(i) + ".png");
				textures.push_back(texture);
			}
			sprite.setTexture(textures[0]);
			sprite.scale(UIElement::MAP_PREVIEW_SIZE / (float)sprite.getTexture()->getSize().x, UIElement::MAP_PREVIEW_SIZE / (float)sprite.getTexture()->getSize().y);
			sprite.setOrigin(sf::Vector2f(sprite.getTexture()->getSize().x / 2.f, sprite.getTexture()->getSize().y / 2.f));
			sprite.setPosition(pos);
			break;

		case UIElement::TYPE_PLAYER_ONE_ARROW:
			texture.loadFromFile("content/Image/UI/Battle/MiniMap/blueArrow.png");
			textures.push_back(texture);
			sprite.setTexture(textures[0]);
			sprite.scale(UIElement::MINIMAP_ARROW_SIZE / (float)sprite.getTexture()->getSize().y, UIElement::MINIMAP_ARROW_SIZE / (float)sprite.getTexture()->getSize().y);
			sprite.setOrigin(sf::Vector2f(sprite.getTexture()->getSize().x / 2.f, sprite.getTexture()->getSize().y / 2.f));
			sprite.setPosition(pos);
			break;

		case UIElement::TYPE_PLAYER_TWO_ARROW:
			texture.loadFromFile("content/Image/UI/Battle/MiniMap/redArrow.png");
			textures.push_back(texture);
			sprite.setTexture(textures[0]);
			sprite.scale(UIElement::MINIMAP_ARROW_SIZE / (float)sprite.getTexture()->getSize().y, UIElement::MINIMAP_ARROW_SIZE / (float)sprite.getTexture()->getSize().y);
			sprite.setOrigin(sf::Vector2f(sprite.getTexture()->getSize().x / 2.f, sprite.getTexture()->getSize().y / 2.f));
			sprite.setPosition(pos);
			break;

		case UIElement::TYPE_CHOOSE_MAP_TEXT:
			texture.loadFromFile("content/Image/UI/ChooseMap/choose_a_map.png");
			textures.push_back(texture);
			sprite.setTexture(textures[0]);
			sprite.scale(120.f / (float)sprite.getTexture()->getSize().y, 120.f / (float)sprite.getTexture()->getSize().y);
			sprite.setOrigin(sf::Vector2f(sprite.getTexture()->getSize().x / 2.f, sprite.getTexture()->getSize().y / 2.f));
			sprite.setPosition(pos);
			break;

		default:
			break;
	}
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
				sprite.setTexture(textures[0]);
			else
				sprite.setTexture(textures[1]);
			break;

		case UIElement::TYPE_PLAYER_ONE_SPEED_BOOSTED:
		case UIElement::TYPE_PLAYER_TWO_SPEED_BOOSTED:
			if (player->status.isSpeedBoosted())
				sprite.setTexture(textures[0]);
			else
				sprite.setTexture(textures[1]);
			break;

		case UIElement::TYPE_PLAYER_ONE_BULLET_BOOSTED:
		case UIElement::TYPE_PLAYER_TWO_BULLET_BOOSTED:
			if (player->status.isBulletBoosted())
				sprite.setTexture(textures[0]);
			else
				sprite.setTexture(textures[1]);
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

		case UIElement::TYPE_PLAYER_WIN_LIGHT_ONE:
			if (player->getPoint() >= 1)
				sprite.setTexture(textures[1]);
			else
				sprite.setTexture(textures[0]);
			break;
		case UIElement::TYPE_PLAYER_WIN_LIGHT_TWO:
			if (player->getPoint() >= 2)
				sprite.setTexture(textures[1]);
			else
				sprite.setTexture(textures[0]);
			break;
		case UIElement::TYPE_PLAYER_WIN_LIGHT_THREE:
			if (player->getPoint() >= 3)
				sprite.setTexture(textures[1]);
			else
				sprite.setTexture(textures[0]);
			break;
		case UIElement::TYPE_CHOOSE_MAP_PREVIEW:
			sprite.setTexture(textures[*target - 1]);
			break;
		case UIElement::TYPE_PLAYER_ONE_ARROW:
		case UIElement::TYPE_PLAYER_TWO_ARROW:
			sprite.setPosition(player->sprite.getPosition());
			sprite.setRotation(player->getDirection());
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