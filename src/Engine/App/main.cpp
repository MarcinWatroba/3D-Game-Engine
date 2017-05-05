#include <Engine/App/Application.h>

int main()
{
	Application app;
	app.create_Window(1080, 720);
	app.run("Game");
	//app.run("Editor");
	return 0;
}