#ifdef BITSOCCER_OSX

#import <Cocoa/Cocoa.h>
#include "osx_main.h"

int main(int argc, char *argv[])
{
	bitsoccer_initialize();
	return 0;
    //return NSApplicationMain(argc,  (const char **) argv);
}

#endif
