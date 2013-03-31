local bit_soccer = Program {
	Name = "bitsoccer",
	Sources = {
		Glob {
			Dir = "src",
			Extensions = { ".cpp", ".c" },
		}
	},

	Env = {
	-- LIBS = {"external/glfw/lib/glfw.a"},
	LIBPATH = {"external/glfw/lib/", "/usr/X11R6/lib/", "/usr/local/lib/"},
	CPPPATH = {"/usr/X11R6/include/", "external/glfw/include/"},
	},
	-- Frameworks = {"Cocoa", "OpenGL"},
	Libs = {
	{"glfw", "GL", "GLU", "m"}},
}

Default(bit_soccer)
