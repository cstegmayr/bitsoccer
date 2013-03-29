#pragma once
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
		virtual void mix(Board* board);
	private:
	}

}
