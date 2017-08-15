#include "Engine.h"

Engine::Engine(int height, int width)
	:m_height(height), m_width(width)
{
	initializeWindow();

	// initialize necessary OpenGL extensions
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
	}

	m_sphfluid = nullptr;

}

Engine::~Engine()
{
	glutDestroyWindow(m_contextHandle);
	glutExit();

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

void Engine::initializeWindow()
{
	// Create GL context
	char fakeParam[] = "fake";
	char *fakeargv[] = { fakeParam, NULL };
	int fakeargc = 1;

	glutInit(&fakeargc, fakeargv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE | GLUT_DEPTH);

	glutInitWindowSize(m_width, m_height);
	int contextHandle = glutCreateWindow("NginR");

}
