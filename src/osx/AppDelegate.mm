//
//  AppDelegate.m
//
//  Created by Christofer Stegmayr on 2011-12-26.
//  Copyright 2013 Stegmayr. All rights reserved.
//

#import "AppDelegate.h"
#ifdef __cplusplus
#include "osx_main.h"
#endif

@implementation CustomAppDelegate

@synthesize window;


- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
	if (!bitsoccer_initialize())
	{
		NSApplication* app = [NSApplication sharedApplication];
		[app terminate: 0];
	}
}

- (void)applicationWillTerminate:(NSNotification *)notification
{
}

@end
