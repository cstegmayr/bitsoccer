#pragma once

#include "Types.h"

namespace bitsoccer
{
	namespace Config
	{
		struct ConfigVar
		{
			union
			{
				int i;
				float f;
				bool b;
			}
			ConfigVarType type;
		};

		const ConfigVar& GetValue(const char* configName);
	}
}

//const ConfigVar& var = Config::GetValue("BoardWidth");
//int test = var.i;
