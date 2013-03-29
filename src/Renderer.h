#pragma once

#include <GL/glfw.h>
#include <GL/GL.h>

namespace bitsoccer
{
	namespace Renderer
	{
		void Initialize(int argc, const char** argv);

		void DrawCallback();
		void Terminate();
		bool IsRunning();

	}
}