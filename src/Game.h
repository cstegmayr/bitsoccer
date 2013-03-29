#include "Types.h"
#include "Board.h"
#include "Ball.h"

namespace bitsoccer
{
	class Game
	{
	public:
		Game();
		void Initialize();
		void Draw();
		void PushBoard(Direction::Type dir, u32 row, u32 col);
		~Game();
	private:
		Board m_board;
		MixerBase* m_mixer;
		Ball* m_ball;
		Brick* m_looseBrick;
	};
}
