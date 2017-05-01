#include <Engine/App/Application.h>
#include <Game/Game/Game.h>
#include <iostream>

Application::Application(const char* pc_GameName)
{
	f_Delta = 0.f;
	f_LastFrame = 0.f;
	f_CurrentFrame = 0.f;
	b_LockedLast = false;
}

Application::~Application()
{
	glfwTerminate();
}

void Application::create_Window(const unsigned short width, const unsigned short height)
{
	//Init GLFW
	glfwInit();

	//Window hints
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Window creation
	po_Window = glfwCreateWindow(width, height, "Robot", nullptr, nullptr);
	if (!po_Window)
	{
		std::cout << "Failed to create a window!" << "\n";
		glfwTerminate();
	}

	//Setup callbacks
	glfwMakeContextCurrent(po_Window);
	glfwSetWindowUserPointer(po_Window, this);
	create_CallBacks();
	
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);


	std::cout << "Window created...!" << "\n";
	std::cout << "Initializing game..." << "\n";
	//Initialize
	glfwSetCursorPos(po_Window, 0.f, 0.f);

	glViewport(0, 0, width, height);
}

void Application::create_CallBacks()
{
	//This way our function doesn't need to be static!
	//We simply cast the pointer from void to our Application
	//We use lambda to capture and create a function
	auto key_callbackFunc = [](GLFWwindow* w, int k, int s, int a, int m)
	{
		static_cast<Application*>(glfwGetWindowUserPointer(w))->key_callback(w, k, s, a, m);
	};

	auto mouse_callbackFunc = [](GLFWwindow* w, int b, int a, int m)
	{
		static_cast<Application*>(glfwGetWindowUserPointer(w))->mouse_button_callback(w, b, a, m);
	};

	glfwSetKeyCallback(po_Window, key_callbackFunc);
	glfwSetMouseButtonCallback(po_Window, mouse_callbackFunc);
}

void Application::run(std::string s_AppType)
{
	if (s_AppType == "Game")
	{
		po_Program = new Game();
		std::cout << "Application runs..." << "\n";
		//Loop
		po_Program->init();
		while (!glfwWindowShouldClose(po_Window))
		{
			//Poll events
			glfwPollEvents();

			if (!po_Program->is_GameOver())
			{
				if (po_Program->is_MouseLocked()) glfwSetInputMode(po_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				else glfwSetInputMode(po_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				
				f_CurrentFrame = (float)glfwGetTime();
				f_Delta = f_CurrentFrame - f_LastFrame;
				f_LastFrame = f_CurrentFrame;

				glfwGetCursorPos(po_Window, &d_MousePosX, &d_MousePosY);
				v2_MousePos = glm::vec2(d_MousePosX, d_MousePosY);

				//Process and update the game
				po_Program->process_Input(f_Delta);
				po_Program->update(f_Delta, v2_MousePos);

				//Rendering
				po_Program->draw();


				glfwSwapBuffers(po_Window);
			}
			else
			{
				glfwSetWindowShouldClose(po_Window, GL_TRUE);
			}
		}
	}
	std::cout << "Cleaning all resources..." << "\n";
}

void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	//Detect ASCII between 0 and 1024
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS) po_Program->process_Key(key, GL_TRUE);
		if (action == GLFW_RELEASE) po_Program->process_Key(key, GL_FALSE);
	}
}

void Application::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS) po_Program->process_Mouse(button, GL_TRUE);
	if (action == GLFW_RELEASE) po_Program->process_Mouse(button, GL_FALSE);
}