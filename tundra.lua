require "tundra.syntax.glob"

Build {
	Configs = {
		Config {
			Name = "macosx-clang",
			DefaultOnHost = "macosx",
			Tools = { "clang-osx" },
		},
	},

	Units = "proj/tundra_config/units.lua",
}