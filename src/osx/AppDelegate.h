//
//  AppDelegate.h
//
//  Created by Christofer Stegmayr on 2011-12-26.
//  Copyright 2013 Stegmayr. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface CustomAppDelegate : NSObject <NSApplicationDelegate> {
    NSWindow *window;
}

@property (assign) IBOutlet NSWindow *window;

@end
