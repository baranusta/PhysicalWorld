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
		glm::vec3 gravity;
		unsigned int integrableInd;
		unsigned int integrableRotInd;

		template<class T>
		int addObject(T obj, std::unordered_map<int, T*> list, unsigned int t)
		{
			list[t] = obj;
		}
	public:
		enum IntegratorTypes { FORWARD_EULER, SEMI_IMPLICIT_EULER, LEAP_FROG, INTEGRATOR_SIZE };
	private:
		std::string integratorShaderSources[3] {"Physics\\PhysicsManagers\\Integrate\\forward_euler_integrator.comp",
												"Physics\\PhysicsManagers\\Integrate\\semi_implicit_euler_integrator.comp" ,
												"Physics\\PhysicsManagers\\Integrate\\leapfrog_integrator.comp" };
		IntegratorTypes m_used_integrator = INTEGRATOR_SIZE;
		void updateShaderController(IntegratorTypes type, float timeStep = 0.01f);

		void _convertDataToNormal(float timeStep);
		void _converDataToRequiredForm(float timeStep);

	protected:
		//It is a map because it might have fluid, solid object.. vs
		std::unordered_map<int, std::shared_ptr<Integrable>> integrables;
		std::unordered_map<int, std::shared_ptr<IntegrableRotating>> integrableRotatings;
		GLuint m_size_index;
		GLuint m_timeStep;
		GLuint m_gravity;

		ComputeShaderController* m_shader;

	public:

		enum IntegrableType {NON_ROTATING, ROTATING};
		Integrator();
		virtual ~Integrator();

		void integrate(float timeStep);
		void setIntegrator(IntegratorTypes integratorType, float timeStep);

		void setGravity(glm::vec3 gravity);

		int addIntegrable(IntegrableType type, std::shared_ptr<Object>);
		void removeIntegrable(IntegrableType type, int id);
	};
}

