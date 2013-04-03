#include "MainLoop.h"

#include "Renderer.h"
#include "Game.h"

#include <GL/glfw.h>
#include <stdio.h>
#include <stdlib.h>

namespace bitsoccer
{
	int MainLoop()
	{
		Renderer::Initialize();

		Game g;
		g.Initialize();

		double time = glfwGetTime();

		do
		{
			double newTime = glfwGetTime(); 
			double dt = newTime - time;
			time = newTime;
			g.Update(dt);
			g.Draw();
			Renderer::DrawCallback();
			glfwSleep(1.0/60.0);
		} while (Renderer::IsRunning());


		return 0;
	}
}
