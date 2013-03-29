local bit_soccer = Program {
	  Name = "Bit-Soccer",
	  Sources = {
	  		  Glob {
			  		Dir = "src",
					Extensions = { ".cpp", ".c" },
					Libs = {"gl"}
			  },
	  },
}

Default(bit_soccer)
