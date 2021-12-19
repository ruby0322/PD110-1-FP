#include "Platform/Platform.hpp"
#include "Entity.hpp"
#include <vector>

class App
{
public:
	void run();
	void init(float, float, const char*);

	App();
	~App();

private:
	util::Platform platform;
	sf::RenderWindow window;
	sf::RenderTexture buffer;

	sf::Clock clock;
	float deltaTime;

	std::vector<Entity*> entities;

	void drawEntities();
	void updateEntities(sf::Event);
};
