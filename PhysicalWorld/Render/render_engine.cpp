#include "render_engine.h"


render_engine::RenderEngine::RenderEngine()
{

}

bool render_engine::RenderEngine::removeRenderer(int id)
{
	if (m_renderers.size() <= id)
		return false;

	m_renderers.erase(m_renderers.begin() + id);
	return true;
}

int render_engine::RenderEngine::addRenderer(std::unique_ptr<Renderer> renderer)
{
	m_renderers.push_back(std::move(renderer));
	return m_renderers.size() - 1;
}

void render_engine::RenderEngine::setRendererVertexCount(int id, int count)
{
	if (m_renderers.size() > id)
		m_renderers[id]->setCount(count);
}

void render_engine::RenderEngine::renderScene(Camera& cam)
{
	for (auto&& renderer : m_renderers)
	{
		renderer->draw(cam);
	}
}
