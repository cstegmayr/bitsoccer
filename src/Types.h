#pragma once

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long u64;

typedef char s8;
typedef short s16;
typedef int s32;
typedef long s64;

namespace bitsoccer
{
	namespace Player
	{
	enum Type
	{
		Red,
		Blue
	};
	}

	namespace Direction
	{
	enum Type
	{
		North,
		East,
		South,
		West,
		NumDirections
	};
	}

	namespace MoveDirection
	{
	enum Type
	{
		FromNorth,
		FromEast,
		FromSouth,
		FromWest,
		ToNorth = FromSouth,
		ToEast = FromWest,
		ToSouth = FromNorth,
		ToWest = FromEast
	};
	}

	namespace Color
	{
	enum Type
	{
		Red = Player::Red,
		Blue = Player::Blue,
        Green,
		RedGoal,
		BlueGoal
	};
	}
}

