#include "App.hpp"
#include "Platform/Platform.hpp"
#include <vector>

App::App() :
	score(0)
{
}

App::~App()
{
}

void App::draw()
{
	buffer.clear(sf::Color(94, 196, 183));
	for (auto& entity : entities)
		buffer.draw(entity->sprite);

	for (auto& text : texts)
		buffer.draw(*text);

	buffer.display();
	window.draw(sf::Sprite(buffer.getTexture()));
	window.display();
}

void App::updateEntities(sf::Event event, float deltaTime)
{
	for (size_t i = 0; i < entities.size(); ++i)
	{
		auto& entity = entities[i];
		entity->update(event, deltaTime);
		if (!(entity->isAlive))
		{
			delete[] entity;
			entities.erase(entities.begin() + i);
		}
	}
}

void App::init(float windowWidth = 400.f,
	float windowHeight = 400.f,
	const char* windowCaption = nullptr)
{

	window.create(sf::VideoMode(windowWidth, windowHeight), windowCaption, sf::Style::Titlebar | sf::Style::Close);
	platform.setIcon(window.getSystemHandle());
	buffer.create(windowWidth, windowHeight);
}

void App::update(sf::Event event)
{
	float deltaTime = clock.restart().asSeconds();
	updateEntities(event, deltaTime);
	for (auto& item : items)
		for (auto& player : players)
			if (item->collidesWith(*player))
			{
				item->reset();
				++score;
				scoreText.setString(std::to_string(score));
				scoreSound.play();
			}
}

void App::run()
{
	sf::Texture tex;
	std::vector<sf::Texture> playerFrames;
	std::string filePath = "content/Image/FatBird/Idle/tile00";
	for (int i = 0; i < 8; ++i)
	{
		tex.loadFromFile(filePath + std::to_string(i) + ".png");
		playerFrames.push_back(tex);
	}

	std::vector<sf::Texture> itemFrames;
	filePath = "content/Image/Apple/tile0";
	for (int i = 0; i < 17; ++i)
	{
		std::string _filePath(filePath);
		if (i < 10)
			_filePath += "0";
		_filePath += std::to_string(i) + ".png";
		tex.loadFromFile(_filePath);
		itemFrames.push_back(tex);
	}

	Player* player1 = new Player(window.getSize().x, window.getSize().y, playerFrames, 10, 1);
	Player* player2 = new Player(window.getSize().x, window.getSize().y, playerFrames, 10, 2);

	entities.push_back(player1);
	entities.push_back(player2);

	players.push_back(player1);
	players.push_back(player2);

	for (auto& player : players)
	{
		player->sprite.setOrigin(player->sprite.getTextureRect().width / 2, player->sprite.getTextureRect().height / 2);
	}

	Item* apple = new Item(window.getSize().x, window.getSize().y, itemFrames, 10);
	entities.push_back(apple);
	items.push_back(apple);

	// std::vector<sf::Texture> bulletFrames(1);
	// bulletFrames[0].loadFromFile("content/Image/Projectile/BlueBullet/tile001.png");

	// Projectile* bullet = new Projectile(bulletFrames, 100, 1);


	// entities.push_back(bullet);
	// projectiles.push_back(bullet);

	font.loadFromFile("content/Font/Arial.ttf");
	scoreText.setFont(font);
	scoreText.setString("0");

	scoreText.setPosition(20.f, 20.f);
	scoreText.setCharacterSize(32);

	texts.push_back(&scoreText);

	sf::SoundBuffer buffer;
	buffer.loadFromFile("content/Audio/score.wav");

	scoreSound.setBuffer(buffer);

	sf::Event event;
	float deltaTime;
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			deltaTime = clock.restart().asSeconds();
			updateEntities(event, deltaTime);
			switch (event.type)
			{
				case sf::Event::Closed:
					window.close();
					break;
				default:
					break;
			}
		}
		update(event);
		draw();
	}
	for (size_t i = 0; i < entities.size(); ++i)
		delete[] entities[i];
}
