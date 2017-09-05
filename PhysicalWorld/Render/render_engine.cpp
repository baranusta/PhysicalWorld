#include "render_engine.h"


render_engine::RenderEngine::RenderEngine()
{

}

render_engine::RenderEngine::~RenderEngine()
{
	for (auto r : m_renderers)
		delete r;
}

bool render_engine::RenderEngine::removeRenderer(int id)
{
	if (m_renderers.size() <= id)
		return false;

	m_renderers.erase(m_renderers.begin() + id);
	return true;
}

int render_engine::RenderEngine::addRenderer(Renderer* renderer)
{
	m_renderers.push_back(renderer);
	return m_renderers.size() - 1;
}

render_engine::Renderer * render_engine::RenderEngine::getRenderer(int id)
{
	if(m_renderers.size()>id)
		return m_renderers[id];
	return nullptr;
}

void render_engine::RenderEngine::renderScene(Camera& cam)
{
	for (auto renderer : m_renderers)
	{
		renderer->draw(cam);
	}
}
