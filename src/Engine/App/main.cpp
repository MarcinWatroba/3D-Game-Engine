#include <Engine/App/Application.h>

int main()
{
	Application app;
	app.create_Window(1920, 1080);
	app.run("Game");
	return 0;
}