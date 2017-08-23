#include "..\stdafx.h"
#include "helper.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Physics
{
	namespace SPH
	{
		TEST_CLASS(SPH)
		{
		private:
			Engine eng;
		public:

			TEST_METHOD(test_ssbo_forces_after_update)
			{
				physics_engine::SPHFluid* fluidSSBO = physics_engine::PhysicsEngine::getInstance().getFluid();
				SPHFluid fluid(fluidSSBO);
				int size = 100;
				std::vector<Particle> particles(size);
				for (int i = 0; i < size; i++)
				{
					Particle p;
					p.position = glm::vec4(100 - i, i, 1, 1);
					particles[i] = p;
				}
				fluid.addParticles(particles);

				physics_engine::PhysicsEngine::getInstance().update();
				glMemoryBarrier(GL_ALL_BARRIER_BITS);

				std::vector<glm::vec4> forces(particles.size());
				getDataFromGPU(fluidSSBO->ssbo[fluidSSBO->FORCE], forces);
				for (int i = 0; i < size; i++)
				{
					Assert::AreEqual(particles[i%size].position.x, forces[i].x);
					Assert::AreEqual(particles[i%size].position.y, forces[i].y);
					Assert::AreEqual(particles[i%size].position.z, forces[i].z);
				}
			}
		};
	}

	namespace Collision
	{

		TEST_CLASS(Collision)
		{
		public:



		};
	}
}