#include <Engine/App/Application.h>

int main()
{
	Application app;
	app.create_Window(1600, 900);
	app.run("Game");
	return 0;
}