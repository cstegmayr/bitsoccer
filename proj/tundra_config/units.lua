require "tundra.syntax.osx-bundle"

local bit_soccer = Program {
	Name = "bitsoccer",
	Sources = {
		FGlob {
			Dir = ".",
			Extensions = { ".cpp", ".c", ".m", ".mm"  },
			Filters = {
				{ Pattern = "x11_"; Config = "x11-*-*" },
				{ Pattern = "win32_"; Config = "win32-*-*" },
				--{ Pattern = "cocoa_"; Config = "macosx-*-*" },
				{ Pattern = "carbon_"; Config = "ignore" },
				{ Pattern = "examples"; Config = "ignore" },
				{ Pattern = "test"; Config = "ignore" },
				{ Pattern = "demo"; Config = "ignore" },
			},
		}
	},

	Env = {
		LIBPATH = {"external/glfw/lib/", "/usr/X11R6/lib/", "/usr/local/lib/"},
		CPPPATH = {"/usr/X11R6/include/", "external/glfw/include/", "external/glfw-2.7.7/lib/cocoa", "external/glfw-2.7.7/lib", "external/"},
		CCOPTS = "-Wall -g -O0",
		CPPDEFS = {"BITSOCCER_OSX"},
	},
	Frameworks = {"Cocoa", "OpenGL", "AppKit", "IOKit", "Foundation"},
	Libs = {
	{"m", "stdc++"}},
}

local clientBundle = OsxBundle {
	Depends = { "bitsoccer" },
	Target = "$(OBJECTDIR)/BitSoccer.app",
	InfoPList = "src/osx/Info.plist",
	Executable = "$(OBJECTDIR)/bitsoccer",
	Resources = {
		CompileNib { Source = "src/osx/en.lproj/MainMenu.xib", Target = "appnib.nib" },
		"src/osx/icon.icns",
		Glob
		{
			Dir = "data",
			Extensions = {".tga", ".ttf"},
		},
	},
}

Default(clientBundle)
