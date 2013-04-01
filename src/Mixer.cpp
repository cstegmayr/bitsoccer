#include "Mixer.h"
#include "Board.h"
#include "Types.h"

#include <stdlib.h>
#include <time.h>

namespace bitsoccer {
	MixerRandom::MixerRandom()
	{
		srand(0); //srand((u32)time(NULL));
	}
	
	u32 GetRandomValue(u32 min, u32 max)
	{
		
		float rnd = (float)rand() / (float)RAND_MAX;

		return (u32)(rnd * (float)(max-min) + 0.5f)+min;
	}

	void MixerRandom::Mix( Board& board )
	{
		const u32 numCols = board.GetWidth();
		const u32 numRows = board.GetHeight();

		for ( u32 i = 0; i < numRows; ++i )
		{
			for ( u32 j = 0; j < numCols; ++j )
			{
				u32 firstColor = 0;
				bool allColorsSame = true;
				for ( u32 k = 0;  k < Direction::NumDirections; ++k )
				{
					u32 randomU32 = GetRandomValue(0, (u32)Color::Green);
					if ( k == 0 )
						firstColor = randomU32;
					allColorsSame &= randomU32 == firstColor;
					if( k == Direction::NumDirections - 1 && allColorsSame )
						randomU32 = (randomU32+1)%Direction::NumDirections;
					Brick* b = board.GetBrick(i,j);
					b->SetColor((Direction::Type)k, (Color::Type)randomU32);

					if (b->IsGoal(Player::Blue) && k== 3 )
						int hej = 0;
					b->NotifyPosition(i,j);
				}
			}
		}
		Brick* b = board.GetBrick(1,1);
		for ( u32 k = 0;  k < Direction::NumDirections; ++k )
			b->SetColor((Direction::Type)k, Color::Blue);
		b = board.GetBrick(numRows-2,numCols-2);
		for ( u32 k = 0;  k < Direction::NumDirections; ++k )
			b->SetColor((Direction::Type)k, Color::Red);

	}

	MixerRandom::~MixerRandom()
	{
	}
 
}
