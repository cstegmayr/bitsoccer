require "tundra.syntax.glob"

Build {
	Configs = {
		Config {
			Name = "clang-osx",
			DefaultOnHost = "macosx",
			Tools = { "clang-osx" },
		},
	},

	Units = "proj/tundra_config/units.lua",
}