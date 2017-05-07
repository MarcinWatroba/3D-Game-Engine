#include <Engine/App/Application.h>

int main()
{
	Application app;
	//app.create_Window(1080, 720);
	//app.run("Game");
	app.create_Window(1920, 1080);
	app.run("Editor");
	return 0;
}