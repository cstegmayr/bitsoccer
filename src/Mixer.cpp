#include "Mixer.h"
#include "Board.h"
#include <random>
namespace bitsoccer {
	MixerRandom::MixerRandom()
	{
	}
	
	void MixerRandom::mix( Board& board )
	{
		const u32 numRows = board.GetWidth();
		const u32 numCols = board.GetHeight();
		for ( u32 i = 0; i < numRows; ++i )
		{
			for ( u32 j = 0; j < numCols; ++j )
			{
				for ( u32 k = 0;  k < Directions::NumDirections; ++k )
				{
					std::default_random_engine generator;
					std::uniform_int_distribution<u32> distribution(0,Directions::NumDirections-1);
					u32 randomU32 = distribution(generator);
					board.getBrick(i,j).SetColor(k,randomU32);
				}
			}
		}
	}

	MixerRandom::~MixerRandom()
	{
	}
 
}
