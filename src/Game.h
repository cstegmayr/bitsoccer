#include "Types.h"
#include "Board.h"

namespace bitsoccer
{
	class Game
	{
	public:
		Game();
		void Initialize();
		void Draw();
		void MakeNextMove(MoveDirection::Type d, u32 position);
		~Game();
	private:
		Board m_board;
	};
}
