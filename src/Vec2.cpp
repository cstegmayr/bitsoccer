#include "Vec2.h"

namespace bitsoccer
{
	Vec2 operator* (float f, Vec2 v)
	{
		return v * f;
	}

	Vec2 operator/ (float f, Vec2 v)
	{
		v.x = f / v.x;
		v.y = f / v.y;
		return v;
	}

	Vec2 operator+ (float f, Vec2 v)
	{
		return v + f;
	}

	Vec2 operator- (float f, Vec2 v)
	{
		v.x = f - v.x;
		v.y = f - v.y;
		return v;
	}
}