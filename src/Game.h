#pragma once

#include "Types.h"
#include "Board.h"
#include "Ball.h"

namespace bitsoccer
{
	class Game
	{
	public:
		Game();
		~Game();
		void Initialize();
		void Draw();
		u32 PushBoard(Direction::Type dir, u32 row, u32 col);
	private:
		Board m_board;
		MixerBase* m_mixer;
		Ball* m_ball;
		Brick* m_looseBrick;
		PlayState::Type m_state;
		u32 m_animationCounter;
	};
}
