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
				--{ Pattern = "main.cpp"; Config = "ignore" },
				--{ Pattern = "cocoa"; Config = "ignore" },
				{ Pattern = "carbon_"; Config = "ignore" },
				{ Pattern = "examples"; Config = "ignore" },
				{ Pattern = "tests"; Config = "ignore" },
			},
		}
	},

	-- Depends = "glfw",

	Env = {
		-- LIBS = {"external/glfw/lib/glfw.a"},
		LIBPATH = {"external/glfw/lib/", "/usr/X11R6/lib/", "/usr/local/lib/"},
		CPPPATH = {"/usr/X11R6/include/", "external/glfw/include/", "external/glfw-2.7.7/lib/cocoa", "external/glfw-2.7.7/lib"},
		CCOPTS = "-Wall -g -O0",
		CPPDEFS = {"BITSOCCER_OSX"},
	},
	Frameworks = {"Cocoa", "OpenGL", "AppKit", "IOKit", "Foundation", "CoreGraphics"},
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
	},
}

Default(clientBundle)
