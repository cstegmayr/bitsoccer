#pragma once
#include "Types.h"
namespace bitsoccer
{
	class Board;
	class MixerBase
	{
	public:
		virtual void mix(Board* board) = 0;
	private:
	};

	class MixerRandom : MixerBase
	{
	public:
		MixerRandom();
		~MixerRandom();
		virtual void Mix(Board* board);
	private:
	};

}
