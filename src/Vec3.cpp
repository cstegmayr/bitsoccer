#include "Vec3.h"

namespace bitsoccer
{
	Vec3 operator* (float f, Vec3 v)
	{
		return v * f;
	}

	Vec3 operator/ (float f, Vec3 v)
	{
		v.x = f / v.x;
		v.y = f / v.y;
		v.z = f / v.z;
		return v;
	}

	Vec3 operator+ (float f, Vec3 v)
	{
		return v+f;
	}

	Vec3 operator- (float f, Vec3 v)
	{
		v.x = f - v.x;
		v.y = f - v.y;
		v.z = f - v.z;
		return v;
	}
}