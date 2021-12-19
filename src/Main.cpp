#include "App.hpp"
#include "Platform/Platform.hpp"
// #include "Sprite.hpp"
int main()
{

	App app;
	app.init(400.f, 400.f, "Testing");
	// Sprite player(&playerTexture, sf::Vector2u(7, 11), 0.1f);

	app.run();

	return 0;
}
