#include "Game.hpp"

int main()
{
	srand(time(nullptr));
	Game* game = new Game();
	game->init(960.f, 960.f, "I\'M Tanker");
	game->run();
	delete game;
	return 0;
}
