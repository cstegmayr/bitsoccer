#include "osx_main.h"

#ifdef BITSOCCER_OSX

#include "../Game.h"
#include "../Renderer.h"
#include <GL/glfw.h>
#include <stdio.h>
#include <stdlib.h>

void GLFWCALL bitsoccer_MainLoop(void *ptr);

static GLFWthread s_threadID = 0;

bool bitsoccer_initialize()
{
	printf("Entered bitsoccer_initialize\n");

	bitsoccer::Renderer::Initialize(0, 0);
	/*s_threadID = glfwCreateThread(bitsoccer_MainLoop, 0);

	printf("Created new thread with id: %d\n", s_threadID);

	return s_threadID >= 0;
	*/

	bitsoccer_MainLoop(0);

	return false;
}

void bitsoccer_MainLoop(void *ptr)
{
	printf("Entered bitsoccer_MainLoop\n");

	using namespace bitsoccer;

	Game g;
	g.Initialize();

	do
	{
		glfwPollEvents();
		g.Draw();
		Renderer::DrawCallback();
		glfwSleep(1.0/60.0);
	} while (Renderer::IsRunning());
}

#endif
