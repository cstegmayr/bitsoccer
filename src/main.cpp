#include "Game.h"
#include "Renderer.h"

#ifndef BITSOCCER_OSX

int main(int argc, const char** argv)
{
	using namespace bitsoccer;
	
	Renderer::Initialize(argc, argv);

	Game g;
	g.Initialize();

	do
	{
		g.Draw();
		Renderer::DrawCallback();
		glfwSleep(1.0/60.0);
	} while (Renderer::IsRunning());


	return 0;
}

#endif
