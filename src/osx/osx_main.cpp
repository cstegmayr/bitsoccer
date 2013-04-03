#include "osx_main.h"

#ifdef BITSOCCER_OSX

#include "../MainLoop.h"

bool bitsoccer_initialize()
{
	return bitsoccer::MainLoop();
}

#endif
