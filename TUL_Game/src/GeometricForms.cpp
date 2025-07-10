#include "GeometricForms.h"

/******************************************************************************
 * 
 * Vec2 Class Definiton
 * 
*******************************************************************************/

Vec2::Vec2():
	x(0), y(0) {}

Vec2::Vec2(float _x, float _y):
	x(_x), y(_y) {}

float Vec2::Magnitude() const
{
	return std::sqrt(x*x + y*y);
}

Vec2 Vec2::Normalized() const
{
	float mag = Magnitude();
	return (mag > 0) ? Vec2(x / mag, y / mag) : Vec2(0, 0);
}

float Vec2::Distance(const Vec2& other) const
{
	return (*this - other).Magnitude();
}

float Vec2::Angle() const
{
	return std::atan2(y, x);
}

Vec2 Vec2::Rotate(float angleRad) const
{
	float cosA = std::cos(angleRad);
	float sinA = std::sin(angleRad);
	return Vec2(x * cosA - y * sinA, y * cosA + x * sinA);
}

float Vec2::AngleBetween(const Vec2& from, const Vec2& to)
{
	return (to - from).Angle();
}

Vec2 Vec2::operator + (const Vec2& other) const
{
	return Vec2(x + other.x, y + other.y);
}

Vec2 Vec2::operator - (const Vec2& other) const
{
	return Vec2(x - other.x, y - other.y);
}

Vec2 Vec2::operator += (const Vec2& other)
{
	x += other.x; y += other.y; return *this;
}

Vec2 Vec2::operator -= (const Vec2& other)
{
	x -= other.x; y -= other.y; return *this;
}

Vec2 Vec2::operator * (float scalar) const
{
	return Vec2(x * scalar, y * scalar);
}

/******************************************************************************
 * 
 * Rect Class Definiton
 * 
*******************************************************************************/

Rect::Rect():
	x(0), y(0), w(0), h(0){}

Rect::Rect(float _x, float _y, float _w, float _h):
	x(_x), y(_y), w(_w), h(_h) {}

Vec2 Rect::Center() const
{
	return Vec2(x + w/2, y + h/2);
}

float Rect::CentersDistanceTo(const Rect& other) const
{
	return Center().Distance(other.Center());
}

bool Rect::Contains(const Vec2& point) const
{
	return point.x >= x
		and point.x <= (x + w)
		and point.y >= y
		and point.y <= (y + h);
}

Rect Rect::operator + (const Vec2& v) const
{
	return Rect(x + v.x, y + v.y, w, h);
}

Rect Rect::operator += (const Vec2& v)
{
	x += v.x; y += v.y; return *this;
}

Rect Rect::operator - (const Vec2& v) const
{
	return Rect(x - v.x, y - v.y, w, h);
}

Rect Rect::operator -= (const Vec2& v)
{
	x -= v.x; y -= v.y; return *this;
}

Rect Rect::operator = (const Vec2& v)
{
	x = v.x; y = v.y; return *this;
}
