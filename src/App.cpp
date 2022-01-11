#include "App.hpp"
#include "Platform/Platform.hpp"

App::App()
{
}

App::~App()
{
}

void App::render()
{
	buffer.clear(sf::Color(94, 196, 183));
	map.draw(buffer);
	for (const auto& entity : entities)
		buffer.draw(entity->sprite);

	for (const auto& text : texts)
		buffer.draw(*text);

	buffer.display();
	window.setView(playerOneView);
	window.draw(sf::Sprite(buffer.getTexture()));
	window.setView(playerTwoView);
	window.draw(sf::Sprite(buffer.getTexture()));
	window.setView(miniMap);
	window.draw(sf::Sprite(buffer.getTexture()));

	// window.setView(window.getDefaultView());
	// draw UI elements

	window.display();
}

void App::init(float windowWidth = 400.f,
	float windowHeight = 400.f,
	const char* windowCaption = nullptr)
{
	window.create(sf::VideoMode(windowWidth, windowHeight), windowCaption, sf::Style::Titlebar | sf::Style::Close);
	platform.setIcon(window.getSystemHandle());
	buffer.create(windowWidth, windowHeight);

	playerOneView.setSize(sf::Vector2f(240.f, 336.f));
	playerOneView.setCenter(sf::Vector2f(0.f, 0.f));
	playerOneView.setViewport(sf::FloatRect(-0.005f, .3f, 0.5f, .7f));
	playerTwoView.setSize(sf::Vector2f(240.f, 336.f));
	playerTwoView.setCenter(sf::Vector2f(0.f, 0.f));
	playerTwoView.setViewport(sf::FloatRect(.505f, .3f, 0.5f, .7f));
	miniMap.setSize(sf::Vector2f(windowWidth, windowHeight));
	miniMap.setCenter(sf::Vector2f(windowWidth / 2.f, windowHeight / 2.f));
	miniMap.setViewport(sf::FloatRect(.36f, .016f, .28f, .28f));


	map.setTargets(&items, &projectiles, &players);
	scene = App::SCENE_BATTLE;
}

void App::updateEntities(const sf::Event& event, float deltaTime)
{
	for (size_t i = 0; i < entities.size(); ++i)
	{
		auto& entity = entities[i];
		entity->update(event, deltaTime);
		if (!(entity->isAlive))
		{
			// delete[] entity;
			// entities.erase(entities.begin() + i);
		}
	}
}

sf::Vector2f App::fixCameraCenter(const sf::Vector2f& pos)
{
	sf::Vector2f fixedPos(pos);

	if (pos.x < playerOneView.getSize().x / 2)
		fixedPos.x = playerOneView.getSize().x / 2;
	else if (pos.x > 960 - playerOneView.getSize().x / 2)
		fixedPos.x = 960 - playerOneView.getSize().x / 2;
	if (pos.y < playerOneView.getSize().y / 2)
		fixedPos.y = playerOneView.getSize().y / 2;
	else if (pos.y > 960 - playerOneView.getSize().y / 2)
		fixedPos.y = 960 - playerOneView.getSize().y / 2;

	return fixedPos;
}

void App::updateCameras()
{
	playerOneView.setCenter(fixCameraCenter(players[0]->sprite.getPosition()));
	playerTwoView.setCenter(fixCameraCenter(players[1]->sprite.getPosition()));
}

// void App::updateProjectiles(const sf::Event& event, float deltaTime)
// {
// }

// void App::updateItems(const sf::Event& event, float deltaTime)
// {
// }

void App::update(const sf::Event& event, float deltaTime)
{
	// updateProjectiles(event, deltaTime);
	// updateItems(event, deltaTime);
	updateCameras();
	updateEntities(event, deltaTime);
	map.update(players, deltaTime);
}

void App::newRound(int mapNumber) {

	int myMap[30][30];
	std::string filePath = "map/map" + std::to_string(mapNumber) + ".txt";
	MapLoader::loadMapFromFile(myMap, filePath);
	map.loadMap(myMap);

	sf::Vector2f playerOnePos;
	sf::Vector2f playerTwoPos;

	for (const auto& tile : map.getTiles()) {
		if (tile->getType() == Tile::TYPE_SPAWNPOINT_ONE) {
			playerOnePos = tile->getSprite().getPosition();
		} else if (tile->getType() == Tile::TYPE_SPAWNPOINT_TWO) {
			playerTwoPos = tile->getSprite().getPosition();
		}
	}

	playerOnePos.x += Tile::TILE_SIZE / 2;
	playerOnePos.y += Tile::TILE_SIZE / 2;
	playerTwoPos.x += Tile::TILE_SIZE / 2;
	playerTwoPos.y += Tile::TILE_SIZE / 2;

	players[0]->reset(playerOnePos);
	players[1]->reset(playerTwoPos);

}

void App::run()
{
	sf::Texture tex;
	std::vector<sf::Texture> player1Frames;
	std::vector<sf::Texture> player2Frames;
	tex.loadFromFile("content/Image/Tank/blue_tank_small.png");
	player1Frames.push_back(tex);
	tex.loadFromFile("content/Image/Tank/red_tank_small.png");
	player2Frames.push_back(tex);

	sf::Vector2f border(window.getSize().x, window.getSize().y);

	Player* player1 = new Player(border, player1Frames, 1);
	Player* player2 = new Player(border, player2Frames, 2);
	player1->sprite.scale(.1f, .1f);
	player2->sprite.scale(.1f, .1f);

	entities.push_back(player1);
	entities.push_back(player2);
	players.push_back(player1);
	players.push_back(player2);

	for (auto& player : players)
		player->sprite.setOrigin(player->sprite.getTextureRect().width / 2, player->sprite.getTextureRect().height / 2);

	newRound(6);
	sf::Event event;
	float deltaTime;
	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		while (window.pollEvent(event))
		{
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
		update(event, deltaTime);
		render();
	}
	for (size_t i = 0; i < entities.size(); ++i)
		delete[] entities[i];
}
