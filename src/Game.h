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
		Color::Type GetMovePlayerColor(const bool includePushState);
		void Draw();
		void Update(double dt);
		PlayState::Type GetState() const;
		bool IsAnimating() const;
		u32 PushBoard(Direction::Type dir, u32 row, u32 col);
	private:
		void UpdatePushState();
		void UpdateMoveState();

		Board m_board;
		MixerBase* m_mixer;
		Ball* m_ball;
		Brick* m_looseBrick;
		PlayState::Type m_state;
		u32 m_animationCounter;
	};
}
