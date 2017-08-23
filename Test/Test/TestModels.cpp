#include "..\stdafx.h"
#include "helper.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;




namespace GameEngine
{
	namespace Model
	{
		namespace Fluid
		{
			TEST_CLASS(FluidModel)
			{
			private:
				Engine eng;
			public:
				TEST_CLASS_INITIALIZE(methodName)
				{
					// test class initialization  code
				}

				TEST_METHOD(add_0_Particles)
				{
					SPHFluid fluid;
					fluid.addParticles({});
					Assert::AreEqual(0, fluid.getParticleCount());
				}

				TEST_METHOD(add_Multiple_Particles)
				{
					SPHFluid fluid;
					fluid.addParticles({ Particle(),Particle() ,Particle() ,Particle() ,Particle() ,
										Particle() ,Particle() ,Particle(),Particle(),Particle() });
					Assert::AreEqual(10, fluid.getParticleCount());
				}

				TEST_METHOD(add_10000_Particles)
				{
					SPHFluid fluid;
					std::vector<Particle> particles(10000);
					fluid.addParticles(particles);
					Assert::AreEqual(10000, fluid.getParticleCount());

				}

				TEST_METHOD(test_ssbo_positions_content_after_addParticle)
				{
					physics_engine::SPHFluid fluidSSBO;
					SPHFluid fluid(&fluidSSBO);
					int size = 100;
					std::vector<Particle> particles(size);
					for (int i = 0; i < size; i++)
					{
						Particle p;
						p.position = glm::vec4(100 - i, i, 1,0);
						particles[i] = p;
					}
					fluid.addParticles(particles);

					std::vector<glm::vec4> positions(particles.size());
					getDataFromGPU(fluidSSBO.ssbo[fluidSSBO.POSITIONS], positions);
					for (int i = 0; i < size; i++)
					{

						Assert::AreEqual(particles[i].position.x, positions[i].x);
						Assert::AreEqual(particles[i].position.y, positions[i].y);
						Assert::AreEqual(particles[i].position.z, positions[i].z);
					}
				}

				TEST_METHOD(test_ssbo_positions_content_after_consecutive_addParticle)
				{
					physics_engine::SPHFluid fluidSSBO;
					SPHFluid fluid(&fluidSSBO);
					int size = 100;
					std::vector<Particle> particles(size);
					for (int i = 0; i < size; i++)
					{
						Particle p;
						p.position = glm::vec4(100 - i, i, 1, 1);
						particles[i] = p;
					}
					fluid.addParticles(particles);
					fluid.addParticles(particles);

					std::vector<glm::vec4> positions(particles.size() * 2);
					getDataFromGPU(fluidSSBO.ssbo[fluidSSBO.POSITIONS], positions);
					for (int i = 0; i < size * 2; i++)
					{

						Assert::AreEqual(particles[i%size].position.x, positions[i].x);
						Assert::AreEqual(particles[i%size].position.y, positions[i].y);
						Assert::AreEqual(particles[i%size].position.z, positions[i].z);
					}
				}
			};
		}
	}
}