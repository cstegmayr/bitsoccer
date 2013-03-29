#pragma once

#include "Types.h"

namespace bitsoccer
{
	class Brick
	{
	public:
		Brick();
		void        SetColor( Direction::Type dir, Color::Type color ) { m_colors[dir] = color; }
		Color::Type GetColor( Direction::Type dir) { return m_colors[dir]; }

	private:
		Color::Type m_colors[Direction::NumDirections];

	};
}
