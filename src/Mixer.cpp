#include "Mixer.h"
#include "Board.h"
#include <random>
namespace bitsoccer {
	MixerRandom::MixerRandom()
	{
	}
	
	void MixerRandom::mix( Board& board )
	{
		const u32 numBricks = board.getSize();
		for ( u32 i = 0; i < numBricks; ++i )
		{
			for ( u32 j = 0;  j < Directions::NumDirections; ++j )
			{
				std::default_random_engine generator;
				std::uniform_int_distribution<u32> distribution(0,Directions::NumDirections-1);
				u32 randomU32 = distribution(generator);
				board.getBrick(i).SetColor(j,randomU32);
			}
		}
	}

	MixerRandom::~MixerRandom()
	{
	}
 
}
