#include "Entity.hpp"
#include "Map.hpp"
#include "Platform/Platform.hpp"
#include <vector>

class App
{
public:
	static const int SCENE_MAIN_MENU = 0;
	static const int SCENE_BATTLE = 1;
	static const int SCENE_PAUSE = 2;
	static const int SCENE_WIN = 3;

	void run();
	void init(float, float, const char*);

	App();
	~App();

private:
	int scene;
	util::Platform platform;
	sf::RenderWindow window;
	sf::RenderTexture buffer;

	sf::Clock clock;

	std::vector<Player*> players;
	std::vector<Entity*> entities;
	std::vector<Item*> items;
	std::vector<Projectile*> projectiles;
	std::vector<sf::Text*> texts;

	sf::View playerOneView;
	sf::View playerTwoView;

	Map map;

	sf::Vector2f fixCameraCenter(const sf::Vector2f& pos);
	void render();
	void update(const sf::Event& event, float deltaTime);
	void updateCameras();
	void updateEntities(const sf::Event& event, float deltaTime);
	void updateItems(const sf::Event& event, float deltaTime);
	void updateProjectiles(const sf::Event& event, float deltaTime);
};
