#include "Game.h"
#include "Renderer.h"

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
	} while (Renderer::IsRunning());


	return 0;
}
