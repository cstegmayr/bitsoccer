

namespace bitsocccer
{
	class Game
	{
	public:
		
		void Initialize();
		void Draw();
		void MakeNextMove(MoveDirection::Type d, u32 position);
	};
}
