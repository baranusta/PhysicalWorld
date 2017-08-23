#include "..\stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

std::ofstream error_file("..\\error_file.txt");

namespace Shaders
{
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
