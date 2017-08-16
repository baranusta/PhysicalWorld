#pragma once
#include "..\stdafx.h"

#include "Renderers\renderer.h"

namespace render_engine
{
	class RenderEngine
	{
	private:
		std::vector<Renderer*> m_renderers;
	private:
		RenderEngine();

	public:
		~RenderEngine();
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
		int addRenderer(Renderer* renderer);
		Renderer* getRenderer(int id);

		void renderScene();

	};
}