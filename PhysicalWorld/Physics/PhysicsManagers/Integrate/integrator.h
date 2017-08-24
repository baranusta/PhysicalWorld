#pragma once

#include <unordered_map>

#include "..\..\Models\integrable.h"
#include "..\..\Models\integrable_rotating.h"
#include "..\..\..\ShaderController\compute_shader_controller.h"


namespace physics_engine
{
	class Integrator
	{
	private:
		unsigned int integrableInd;
		unsigned int integrableRotInd;

		template<class T>
		int addObject(T obj, std::unordered_map<int, T*> list, unsigned int t)
		{
			list[t] = obj;
		}

		enum IntegratorTypes { EULER, INTEGRATOR_SIZE };
		std::string integratorShaderSources[1] {"Physics\\PhysicsManagers\\Integrate\\euler_integrator.comp"};
		IntegratorTypes m_used_integrator = INTEGRATOR_SIZE;
		void updateShaderController(IntegratorTypes type);

	protected:
		std::unordered_map<int, Integrable*> integrables;
		std::unordered_map<int, IntegrableRotating*> integrableRotatings;
		GLuint m_size_index;
		GLuint m_timeStep;

		ComputeShaderController* m_shader;

	public:
		enum IntegrableType {NON_ROTATING, ROTATING};
		Integrator();
		virtual ~Integrator();

		void integrate(float timeStep);

		int addIntegrable(IntegrableType type, Object*);
		void removeIntegrable(IntegrableType type, int id);
	};
}

