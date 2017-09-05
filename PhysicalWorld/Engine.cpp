#include "Engine.h"

void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

Engine::Engine(glm::vec2 size)
	:m_size(size), m_scene_manager(size)
{
	initializeWindow();

	// initialize necessary OpenGL extensions
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
	}

	GLuint err;
	while ((err = glGetError()) != GL_NO_ERROR);
}

Engine::~Engine()
{
	glfwDestroyWindow(window); 
	glfwTerminate();
}

void Engine::setScene(Scene * scene)
{
	m_scene_manager.clean();
	m_scene_manager.resolveScene(scene);
}

void Engine::startGame(std::function<void(void)> gameloop)
{
	{
		glEnable(GL_DEPTH_TEST);
		while (!glfwWindowShouldClose(window)) {
			glfwPollEvents();
			glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			m_scene_manager.update();
			gameloop();
			physics_engine::PhysicsEngine::getInstance().update(m_timeStep);
			for(auto camera: m_scene_manager.getCameras())
				render_engine::RenderEngine::getInstance().renderScene(*camera);
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

	window = glfwCreateWindow(m_size.x, m_size.y, "NginR", nullptr, nullptr);
	if (!window) {
		throw "can not initialize no window";
	}
	// Activate the OpenGL context
	glfwMakeContextCurrent(window);

	// Initialize GLEW extension loader
	glewExperimental = GL_TRUE;

	InputController::getInstance().init(window);
}
