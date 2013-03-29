#include "Mixer.h"
#include "Board.h"
#include "Types.h"

#include <stdlib.h>
#include <time.h>

namespace bitsoccer {
	MixerRandom::MixerRandom()
	{
		srand((u32)time(NULL));
	}
	
	u32 GetRandomValue(u32 min, u32 max)
	{
		
		float rnd = (float)rand() / (float)RAND_MAX;

		return (u32)(rnd * (float)(max-min) + 0.5f)+min;
	}

	void MixerRandom::Mix( Board& board )
	{
		const u32 numRows = board.GetWidth();
		const u32 numCols = board.GetHeight();
		for ( u32 i = 0; i < numRows; ++i )
		{
			for ( u32 j = 0; j < numCols; ++j )
			{
				for ( u32 k = 0;  k < Direction::NumDirections; ++k )
				{
					u32 randomU32 = GetRandomValue(0, (u32)Color::Green);
					board.GetBrick(i,j)->SetColor((Direction::Type)k, (Color::Type)randomU32);
				}
			}
		}
	}

	MixerRandom::~MixerRandom()
	{
	}
 
}
