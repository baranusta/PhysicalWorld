#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\PhysicalWorld\Models\SPHFluid\sph_fluid.h"
#include "..\PhysicalWorld\Engine.h"

#include "..\PhysicalWorld\ShaderController\compute_shader_controller.h"
#include "..\PhysicalWorld\ShaderController\render_shader_controller.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;



std::ofstream error_file("..\\error_file.txt");

template<class T>
void getDataFromGPU(GLuint buffer, std::vector<T>& data)
{
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, buffer); // 
	GLvoid* s = glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_ONLY);

	memcpy(&data[0], s, sizeof(T) * data.size());
	glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
}

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

				TEST_METHOD(test_ssbo_positions_content_after_update)
				{
					physics_engine::SPHFluid* fluidSSBO = physics_engine::PhysicsEngine::getInstance().getFluid();
					SPHFluid fluid(fluidSSBO);
					int size = 100;
					std::vector<Particle> particles(size);
					for (int i = 0; i < size; i++)
					{
						Particle p;
						p.position = glm::vec4(100 - i, i, 1,1);
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
	}
	namespace EngineItself
	{
		TEST_CLASS(EngineClass)
		{
		private:
			Engine eng;
		public:
			TEST_CLASS_INITIALIZE(methodName)
			{
				// test class initialization  code
			}

			TEST_METHOD(is_sphfluid_initially_null)
			{
				Assert::AreEqual(0, eng.getSPHFluid() == nullptr ? 0 : 1);
			}

			TEST_METHOD(is_sphfluid_remove_crashing_when_null)
			{
				eng.removeSPHFluid();
				Assert::AreEqual(0, eng.getSPHFluid() == nullptr ? 0:1);

			}

			TEST_METHOD(is_sphfluid_can_added_success)
			{
				eng.addSPHFluid();
				Assert::AreNotEqual(0, eng.getSPHFluid() == nullptr ? 0 : 1);
			}

			TEST_METHOD(is_sphfluid_can_removed_success)
			{
				std::ofstream file("wow.txt");
				eng.addSPHFluid();
				Assert::AreNotEqual(0, eng.getSPHFluid() == nullptr ? 0 : 1);
				eng.removeSPHFluid();
				Assert::AreEqual(0, eng.getSPHFluid() == nullptr ? 0 : 1);
			}
		};
	}
	namespace ShaderControllers
	{
		TEST_CLASS(ComputeShader)
		{
		private:
			Engine eng;
		public:
			TEST_CLASS_INITIALIZE(methodName)
			{
				// test class initialization  code
			}

			TEST_METHOD(compute_shader_is_not_exist)
			{
				try {
					ShaderController* compute = new ComputeShaderController("compute_shaders.glsl");
					
				}
				catch (std::string& msg)
				{
					Assert::IsTrue(true);
					return;
				}
				catch (...)
				{

				}
				Assert::IsTrue(false);
			}
			
			TEST_METHOD(compute_shader_is_exist)
			{
				try {
					ShaderController* compute = new ComputeShaderController("..\\Test\\Resource\\compute_shader_wrong.glsl");
				}
				catch (const char* msg)
				{
					Assert::IsTrue(false);
					return;
				}
				catch (...)
				{

				}
				Assert::IsTrue(true);
			}

			TEST_METHOD(compute_shader_is_exist_compile_error)
			{
				try {
					ShaderController* compute = new ComputeShaderController("..\\Test\\Resource\\compute_shader_wrong.glsl");
				}
				catch (std::logic_error err)
				{
					error_file << err.what();
					Assert::IsTrue(true);
					return;
				}
				catch (...)
				{

				}
				Assert::IsTrue(false);
			}

			TEST_METHOD(compute_shader_is_exist_no_error)
			{
				try {
					ShaderController* compute = new ComputeShaderController("..\\Test\\Resource\\compute_shader_correct.glsl");
				}
				catch (...)
				{
					Assert::IsTrue(false);
					return;
				}
				Assert::IsTrue(true);
			}
		};
	}
}



namespace Physics
{
	namespace Engine
	{
		TEST_CLASS(a)
		{
		public:



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