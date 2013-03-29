#include "Types.h"
#include "Brick.h"

namespace bitsocccer
{
	class Game
	{
	public:
		Game();
		void Initialize();
		void Draw();
		void MakeNextMove(MoveDirection::Type d, u32 position);
		~Game();
	};
}
