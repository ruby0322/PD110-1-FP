#include "Button.hpp"

Button::Button(int type, int* event, const sf::Vector2f& pos) :
	Entity(),
	event(event)
{
	this->clicked = false;
	this->type = type;
	sf::Texture tex;
	sprite.setPosition(pos);
	switch (type)
	{
		case Button::TYPE_PLAY:
		case Button::TYPE_CHOOSE_MAP_PLAY:
			tex.loadFromFile("content/Image/UI/MainMenu/PlayButton/Play_Unpressed.png");
			frames.push_back(tex);
			tex.loadFromFile("content/Image/UI/MainMenu/PlayButton/Play_Pressed.png");
			frames.push_back(tex);
			sprite.setTexture(frames[0]);
			sprite.scale(Button::BUTTON_HEIGHT / (float)sprite.getTexture()->getSize().y, Button::BUTTON_HEIGHT / (float)sprite.getTexture()->getSize().y);
			break;
		case Button::TYPE_INFO:
			tex.loadFromFile("content/Image/UI/MainMenu/InfoButton/Info_Unpressed.png");
			frames.push_back(tex);
			tex.loadFromFile("content/Image/UI/MainMenu/InfoButton/Info_Pressed.png");
			frames.push_back(tex);
			sprite.setTexture(frames[0]);
			sprite.scale(Button::BUTTON_HEIGHT / (float)sprite.getTexture()->getSize().y, Button::BUTTON_HEIGHT / (float)sprite.getTexture()->getSize().y);
			break;

		case Button::TYPE_HOW_TO_PLAY_BACK:
			tex.loadFromFile("content/Image/UI/HowToPlay/CrossButton/Cross_Unpressed.png");
			frames.push_back(tex);
			tex.loadFromFile("content/Image/UI/HowToPlay/CrossButton/Cross_Pressed.png");
			frames.push_back(tex);
			sprite.setTexture(frames[0]);
			sprite.scale(Button::BUTTON_HEIGHT / (float)sprite.getTexture()->getSize().y, Button::BUTTON_HEIGHT / (float)sprite.getTexture()->getSize().y);
			break;

		case Button::TYPE_PAUSE:
			tex.loadFromFile("content/Image/UI/Pause/PauseButton/Pause_Unpressed.png");
			frames.push_back(tex);
			tex.loadFromFile("content/Image/UI/Pause/PauseButton/Pause_Pressed.png");
			frames.push_back(tex);
			sprite.setTexture(frames[0]);
			sprite.scale(Button::BUTTON_HEIGHT / (float)sprite.getTexture()->getSize().y, Button::BUTTON_HEIGHT / (float)sprite.getTexture()->getSize().y);
			break;

		case Button::TYPE_PAUSE_BACK:
			tex.loadFromFile("content/Image/UI/Pause/CrossButton/Cross_Unpressed.png");
			frames.push_back(tex);
			tex.loadFromFile("content/Image/UI/Pause/CrossButton/Cross_Pressed.png");
			frames.push_back(tex);
			sprite.setTexture(frames[0]);
			sprite.scale(Button::BUTTON_HEIGHT / (float)sprite.getTexture()->getSize().y, Button::BUTTON_HEIGHT / (float)sprite.getTexture()->getSize().y);
			break;

		case Button::TYPE_PAUSE_RESET:
			tex.loadFromFile("content/Image/UI/Pause/BackwardButton/Backward_Unpressed.png");
			frames.push_back(tex);
			tex.loadFromFile("content/Image/UI/Pause/BackwardButton/Backward_Pressed.png");
			frames.push_back(tex);
			sprite.setTexture(frames[0]);
			sprite.scale(Button::BUTTON_HEIGHT / (float)sprite.getTexture()->getSize().y, Button::BUTTON_HEIGHT / (float)sprite.getTexture()->getSize().y);
			break;
		case Button::TYPE_VICTORY_RESET:
			tex.loadFromFile("content/Image/UI/Victory/BackwardButton/Backward_Unpressed.png");
			frames.push_back(tex);
			tex.loadFromFile("content/Image/UI/Victory/BackwardButton/Backward_Pressed.png");
			frames.push_back(tex);
			sprite.setTexture(frames[0]);
			sprite.scale(Button::BUTTON_HEIGHT / (float)sprite.getTexture()->getSize().y, Button::BUTTON_HEIGHT / (float)sprite.getTexture()->getSize().y);
			break;

		case Button::TYPE_CHOOSE_MAP_NEXT:
			tex.loadFromFile("content/Image/UI/ChooseMap/ForwardButton/Forward_Unpressed.png");
			frames.push_back(tex);
			tex.loadFromFile("content/Image/UI/ChooseMap/ForwardButton/Forward_Pressed.png");
			frames.push_back(tex);
			sprite.setTexture(frames[0]);
			sprite.scale(Button::BUTTON_HEIGHT / (float)sprite.getTexture()->getSize().y, Button::BUTTON_HEIGHT / (float)sprite.getTexture()->getSize().y);
			break;

		case Button::TYPE_CHOOSE_MAP_PREV:
			tex.loadFromFile("content/Image/UI/Victory/BackwardButton/Backward_Unpressed.png");
			frames.push_back(tex);
			tex.loadFromFile("content/Image/UI/Victory/BackwardButton/Backward_Pressed.png");
			frames.push_back(tex);
			sprite.setTexture(frames[0]);
			sprite.scale(Button::BUTTON_HEIGHT / (float)sprite.getTexture()->getSize().y, Button::BUTTON_HEIGHT / (float)sprite.getTexture()->getSize().y);
			break;

		default:
			break;
	}
	resetCenter();
}

Button::~Button()
{
}

bool Button::isPointInside(const sf::Vector2f& pos) const
{

	return sprite.getGlobalBounds().contains(pos);
}

void Button::trigger()
{
	switch (type)
	{
		case Button::TYPE_PLAY:
			*event = Button::EVENT_CHOOSE_MAP;
			break;
		case Button::TYPE_CHOOSE_MAP_PLAY:
			*event = Button::EVENT_NEW_ROUND;
			break;
		case Button::TYPE_INFO:
			*event = Button::EVENT_HOW_TO_PLAY;
			break;
		case Button::TYPE_MAIN_MENU:
			*event = Button::EVENT_MAIN_MENU;
			break;
		case Button::TYPE_HOW_TO_PLAY_BACK:
			*event = Button::EVENT_MAIN_MENU;
			break;
		case Button::TYPE_PAUSE:
			*event = Button::EVENT_PAUSE_RESUME;
			break;
		case Button::TYPE_PAUSE_BACK:
			*event = Button::EVENT_NEW_GAME;
			break;
		case Button::TYPE_PAUSE_RESET:
			*event = Button::EVENT_NEW_ROUND;
			break;
		case Button::TYPE_VICTORY_RESET:
			*event = Button::EVENT_NEW_GAME;
			break;
		case Button::TYPE_CHOOSE_MAP_NEXT:
			*event = Button::EVENT_NEXT_MAP;
			break;
		case Button::TYPE_CHOOSE_MAP_PREV:
			*event = Button::EVENT_PREV_MAP;
			break;
		default:
			break;
	}
}

void Button::handleEvent(const sf::Event& event)
{
	switch (event.type)
	{
		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left)
				if (isPointInside(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
				{
					clicked = true;
					setFrame(1);
				}
			break;
		case sf::Event::MouseButtonReleased:
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				setFrame(0);
				if (isPointInside(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
					if (clicked)
					{
						trigger();
						SoundManager::PlaySoundEffect(SoundManager::TYPE_BUTTON_PRESSED);
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