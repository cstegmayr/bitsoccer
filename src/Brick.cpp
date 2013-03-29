#include "Brick.h"
#include "Types.h"

#include <memory.h> // for memset

namespace bitsoccer
{
	Brick::Brick()
	{
		memset(m_colors, (int)Color::Green, sizeof(m_colors));
	}
}
