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
		public:

			TEST_METHOD(addParticleWithNoFluidBefore)
			{
				// TODO: Your test code here
				SPHFluid a;
				Assert::AreEqual(unsigned int(-1), a.getParticleSIndex());
				a.addParticles({Particle()});
				Assert::AreEqual(unsigned int(0), a.getParticleSIndex());
			}

			TEST_METHOD(addParticleWithFluidBefore)
			{
				// TODO: Your test code here
				SPHFluid a;
				SPHFluid b;
				a.addParticles({ Particle() });
				b.addParticles({ Particle() });
				Assert::AreNotEqual(unsigned int(1), b.getParticleSIndex());
				Assert::AreNotEqual(unsigned int(0), a.getParticleSIndex());
			}

			TEST_METHOD(addParticleWithFluidBeforeIndexCheck)
			{
				// TODO: Your test code here
				SPHFluid a;
				SPHFluid b;
				a.addParticles({ Particle(),Particle(),Particle() });
				b.addParticles({ Particle() });
				Assert::AreNotEqual(unsigned int(2), b.getParticleSIndex());
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