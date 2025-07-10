#ifndef GEOMETRICFORMS_H
#define GEOMETRICFORMS_H

#include <cmath>

class Vec2
{
public:
	float x, y;
	Vec2();
	Vec2(float _x, float _y);

	float Magnitude() const;
	Vec2 Normalized() const;
	float Distance(const Vec2& other) const;
	float Angle() const;
	Vec2 Rotate(float angleRad) const;

	static float AngleBetween(const Vec2& from, const Vec2& to);

	Vec2 operator + (const Vec2& other) const;
	Vec2 operator - (const Vec2& other) const;
	Vec2 operator += (const Vec2& other);
	Vec2 operator -= (const Vec2& other);
	Vec2 operator * (float scalar) const;
};

class Rect
{
public:
	float x, y, w, h;
	Rect();
	Rect(float _x, float _y, float _w, float _h);
	Vec2 Center() const;
	float CentersDistanceTo(const Rect& other) const;
	bool Contains(const Vec2& point) const;

	Rect operator + (const Vec2& v) const;
	Rect operator += (const Vec2& v);
	Rect operator - (const Vec2& v) const;
	Rect operator -= (const Vec2& v);
	Rect operator = (const Vec2& v);
};

#endif
