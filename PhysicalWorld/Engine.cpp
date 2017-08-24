#include "Engine.h"

void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

Engine::Engine(int height, int width)
	:m_height(height), m_width(width)
{
	initializeWindow();

	// initialize necessary OpenGL extensions
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
	}

	GLuint err;
	while ((err = glGetError()) != GL_NO_ERROR);

	m_sphfluid = nullptr;

}

Engine::~Engine()
{
	glfwDestroyWindow(window); 
	glfwTerminate();
	removeSPHFluid();
}

SPHFluid* Engine::getSPHFluid()
{
	return m_sphfluid;
}

void Engine::addSPHFluid()
{
	m_sphfluid = new SPHFluid();
}

void Engine::removeSPHFluid()
{
	if (m_sphfluid != nullptr)
		delete m_sphfluid;
	m_sphfluid = nullptr;
}

void Engine::startGame(std::function<void(void)> gameloop)
{
	{
		glEnable(GL_DEPTH_TEST);
		while (!glfwWindowShouldClose(window)) {
			glfwPollEvents();
			glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			gameloop();
			physics_engine::PhysicsEngine::getInstance().update(m_timeStep);
			render_engine::RenderEngine::getInstance().renderScene();
			glfwSwapBuffers(window);
		}
	}
}

void Engine::initializeWindow()
{
	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) {
		throw "can not initialize glfw";
	}


	// Create window and OpenGL 4.3 debug context
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(m_width, m_height, "NginR", nullptr, nullptr);
	if (!window) {
		throw "can not initialize no window";
	}
	// Activate the OpenGL context
	glfwMakeContextCurrent(window);

	// Initialize GLEW extension loader
	glewExperimental = GL_TRUE;

}
