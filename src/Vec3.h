#pragma once

#include <math.h>

namespace bitsoccer
{
	class Vec3
	{
	public:
		Vec3() : x(0), y(0), z(0) {}
		Vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
		Vec3(const Vec3& v) : x(v.x), y(v.y), z(v.z) {}
		union
		{
			struct {float r,g,b;};
			struct {float x,y,z;};
		};

		Vec3& operator*= (const Vec3& v)
		{
			x *= v.x;
			y *= v.y;
			z *= v.z;

			return (*this);
		}

		Vec3& operator/= (const Vec3& v)
		{
			x /= v.x;
			y /= v.y;
			z /= v.z;

			return (*this);
		}

		Vec3& operator+= (const Vec3& v)
		{
			x += v.x;
			y += v.y;
			z += v.z;

			return (*this);
		}

		Vec3& operator-= (const Vec3& v)
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;

			return (*this);
		}

		Vec3 operator* (const Vec3& v) const
		{
			Vec3 r(*this);
			r *= v;

			return r;
		}

		Vec3 operator/ (const Vec3& v) const
		{
			Vec3 r(*this);
			r /= v;

			return r;
		}

		Vec3 operator+ (const Vec3& v) const
		{
			Vec3 r(*this);
			r += v;

			return r;
		}

		Vec3 operator- (const Vec3& v) const
		{
			Vec3 r(*this);
			r -= v;

			return r;
		}

		Vec3& operator*= (float f)
		{
			x *= f;
			y *= f;
			z *= f;
			return *this;
		}

		Vec3& operator/= (float f)
		{
			x /= f;
			y /= f;
			z /= f;
			return *this;
		}

		Vec3& operator+= (float f)
		{
			x += f;
			y += f;
			z += f;
			return *this;
		}

		Vec3& operator-= (float f)
		{
			x -= f;
			y -= f;
			z -= f;
			return *this;
		}

		Vec3 operator* (float f) const
		{
			Vec3 r(*this);
			r *= f;
			return r;
		}

		Vec3 operator/ (float f) const
		{
			Vec3 r(*this);
			r /= f;
			return r;
		}

		Vec3 operator+ (float f) const
		{
			Vec3 r(*this);
			r += f;
			return r;
		}

		Vec3 operator- (float f) const
		{
			Vec3 r(*this);
			r -= f;
			return r;
		}

		float Dot(const Vec3& v) const
		{
			return x*v.x + y*v.y + z*v.z;
		}

		float Length2() const
		{
			return Dot(*this);
		}

		float Length() const
		{
			return sqrtf(Length2());
		}
	};

	Vec3 operator* (float f, Vec3 v);
	Vec3 operator/ (float f, Vec3 v);
	Vec3 operator+ (float f, Vec3 v);
	Vec3 operator- (float f, Vec3 v);
}
