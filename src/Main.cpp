#include "App.hpp"
#include "Platform/Platform.hpp"
#include <ctime>
// #include "Sprite.hpp"
int main()
{
	srand(time(nullptr));
	App app;
	app.init(1400.f, 800.f, "Testing");
	// Sprite player(&playerTexture, sf::Vector2u(7, 11), 0.1f);

	app.run();

	return 0;
}
