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

			const double wantedFrametime = 1.0 / 30.0;
			const double sleepThreshold = 1.0/1000.0;
			double sleepTime = wantedFrametime - (glfwGetTime() - newTime) - sleepThreshold;
			if (sleepTime > 0.0)
				glfwSleep(sleepTime);
		} while (Renderer::IsRunning());


		return 0;
	}
}
