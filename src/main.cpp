#include "Game.h"
#include "Renderer.h"

#ifndef BITSOCCER_OSX

int main(int argc, const char** argv)
{
	using namespace bitsoccer;
	
	Renderer::Initialize(argc, argv);

	Game g;
	g.Initialize();

	double time = glfwGetTime();

	do
	{
		double newTime = glfwGetTime(); 
		double dt = newTime - time;
		time = newTime;
		g.Update(dt)
		g.Draw();
		Renderer::DrawCallback();
		glfwSleep(1.0/60.0);
	} while (Renderer::IsRunning());


	return 0;
}

#endif
