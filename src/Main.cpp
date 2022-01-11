#include "App.hpp"
#include <ctime>

int main()
{
	srand(time(nullptr));
	App app;
	app.init(960.f, 960.f, "I\'M Tanker");

	app.run();

	return 0;
}
