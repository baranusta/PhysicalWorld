#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\PhysicalWorld\Models\SPHFluid\sph_fluid.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Model
{
	namespace Fluid
	{
		TEST_CLASS(FluidModel)
		{
		private:
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
				fluid.addParticles({Particle(),Particle() ,Particle() ,Particle() ,Particle() ,
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