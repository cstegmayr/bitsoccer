#pragma once

#include <math.h>

namespace bitsoccer
{
	class Vec2
	{
	public:
		Vec2() : x(0), y(0) {}
		Vec2(float _x, float _y) : x(_x), y(_y) {}
		Vec2(const Vec2& v) : x(v.x), y(v.y) {}
		union
		{
			struct {float s,t;};
			struct {float x,y;};
		};

		Vec2& operator*= (const Vec2& v)
		{
			x *= v.x;
			y *= v.y;

			return (*this);
		}

		Vec2& operator/= (const Vec2& v)
		{
			x /= v.x;
			y /= v.y;

			return (*this);
		}

		Vec2& operator+= (const Vec2& v)
		{
			x += v.x;
			y += v.y;

			return (*this);
		}

		Vec2& operator-= (const Vec2& v)
		{
			x -= v.x;
			y -= v.y;

			return (*this);
		}

		Vec2 operator* (const Vec2& v) const
		{
			Vec2 r(*this);
			r *= v;

			return r;
		}

		Vec2 operator/ (const Vec2& v) const
		{
			Vec2 r(*this);
			r /= v;

			return r;
		}

		Vec2 operator+ (const Vec2& v) const
		{
			Vec2 r(*this);
			r += v;

			return r;
		}

		Vec2 operator- (const Vec2& v) const
		{
			Vec2 r(*this);
			r -= v;

			return r;
		}

		Vec2& operator*= (float f)
		{
			x *= f;
			y *= f;
			return *this;
		}

		Vec2& operator/= (float f)
		{
			x /= f;
			y /= f;
			return *this;
		}

		Vec2& operator+= (float f)
		{
			x += f;
			y += f;
			return *this;
		}

		Vec2& operator-= (float f)
		{
			x -= f;
			y -= f;
			return *this;
		}

		Vec2 operator* (float f) const
		{
			Vec2 r(*this);
			r *= f;
			return r;
		}

		Vec2 operator/ (float f) const
		{
			Vec2 r(*this);
			r /= f;
			return r;
		}

		Vec2 operator+ (float f) const
		{
			Vec2 r(*this);
			r += f;
			return r;
		}

		Vec2 operator- (float f) const
		{
			Vec2 r(*this);
			r -= f;
			return r;
		}

		float Dot(const Vec2& v) const
		{
			return x*v.x + y*v.y;
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

	Vec2 operator* (float f, Vec2 v);
	Vec2 operator/ (float f, Vec2 v);
	Vec2 operator+ (float f, Vec2 v);
	Vec2 operator- (float f, Vec2 v);
}