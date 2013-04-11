#pragma once

#define _USE_MATH_DEFINES

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
		NumDirections // Beautiful
	};
	}

	namespace MoveDirection
	{
	enum Type
	{
		ToNorth = 1<<0, // 1
		ToEast = 1<<1,  // 2
		ToSouth = 1<<2, // 4
		ToWest = 1<<3,  // 8
		FromNorth = ToSouth,
		FromEast = ToWest,
		FromSouth = ToNorth,
		FromWest = ToEast
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

	namespace HitState
	{
	enum Type
	{
		Hold,
		Pressed,
		Released
	};
	}
	
	namespace PlayState
	{
	enum Type 
	{
		PlayerRedPush,
		PlayerRedMove,
		PlayerBluePush,
		PlayerBlueMove
	};
	}

	namespace BrickMode
	{
		enum Type
		{
			Normal       = 0,
			RedGoal      = 1<<0,
			BlueGoal     = 1<<1,
			PossibleMove = 1<<2
		};

	}
}

