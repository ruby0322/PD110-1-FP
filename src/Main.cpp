#include "App.hpp"
#include <ctime>

int main()
{
	srand(time(nullptr));
	App app;
	app.init(960.f, 960.f, "Testing");

	app.run();

	return 0;
}
