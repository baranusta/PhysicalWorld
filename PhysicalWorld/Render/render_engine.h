#pragma once
#include "..\stdafx.h"

#include "Renderers\renderer.h"

namespace render_engine
{
	class RenderEngine
	{
	private:
		std::vector<std::unique_ptr<Renderer>> m_renderers;
	private:
		RenderEngine();

	public:
		RenderEngine(RenderEngine&) = delete;
		void operator=(RenderEngine&) = delete;

		static RenderEngine& getInstance()
		{
			static RenderEngine engine;
			return engine;
		}

	public:
		bool removeRenderer(int id);

		//If the owner of the renderer is destructed, the renderer has to be removed.
		int addRenderer(std::unique_ptr<Renderer> renderer);
		void setRendererVertexCount(int id, int count);

		void renderScene(Camera& cam);

	};
}