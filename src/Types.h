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
		North = 1<<0,
		East = 1<<1,
		South = 1<<2,
		West = 1<<3,
		NumDirections = 4 // ugly
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

	namespace ConfigVarType
	{
	enum Type 
	{
		Int,
		Float,
		Bool
	};
	}
}

