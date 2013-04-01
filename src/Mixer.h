#pragma once
#include "Types.h"
namespace bitsoccer
{
	class Board;
	
	class MixerBase
	{
	public:
		virtual ~MixerBase() {}
		virtual void Mix(Board& board) = 0;
	private:
	};

	class MixerRandom : public MixerBase
	{
	public:
		MixerRandom();
		virtual ~MixerRandom();
		virtual void Mix(Board& board);
	private:
	};

}
