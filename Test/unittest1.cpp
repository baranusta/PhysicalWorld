#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\PhysicalWorld\Models\SPHFluid\sph_fluid.h"
#include "..\PhysicalWorld\Engine.h"

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
				SPHFluid fluid;
			public:
				TEST_CLASS_INITIALIZE(methodName)
				{
					// test class initialization  code
				}

				TEST_METHOD(add_0_Particles)
				{
					fluid.addParticles({});
					Assert::AreEqual(0, fluid.getParticleCount());
				}

				TEST_METHOD(add_Multiple_Particles)
				{
					fluid.addParticles({ Particle(),Particle() ,Particle() ,Particle() ,Particle() ,
										Particle() ,Particle() ,Particle(),Particle(),Particle() });
					Assert::AreEqual(10, fluid.getParticleCount());

				}

				TEST_METHOD(add_10000_Particles)
				{
					std::vector<Particle> particles(10000);
					fluid.addParticles(particles);
					Assert::AreEqual(10000, fluid.getParticleCount());

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
				eng.addSPHFluid();
				Assert::AreNotEqual(0, eng.getSPHFluid() == nullptr ? 0 : 1);
				eng.removeSPHFluid();
				Assert::AreEqual(0, eng.getSPHFluid() == nullptr ? 0 : 1);
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