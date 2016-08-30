#include "Point.h"

Point::Point() : x(0.0f), y(0.0f)
{
}

Point::Point(float _x, float _y) : x(_x), y(_y)
{
}

Point::Point(const Point & p) : x(p.x), y(p.y)
{
}

Point::~Point()
{
}

Point Point::operator+(const Point & p) const
{
	return Point(x + p.x, y + p.y);
}

Point Point::operator+(float f) const
{
	return Point(x + f, y + f);
}

Point Point::operator-(const Point & p) const
{
	return Point(x - p.x, y - p.y);
}

Point Point::operator-(float f) const
{
	return Point(x - f, y - f);
}

Point Point::operator*(const Point & p) const
{
	return Point(x * p.x, y * p.y);
}

Point Point::operator*(float f) const
{
	return Point(x * f, y * f);
}

Point Point::operator/(const Point & p) const
{
	assert(p.x != 0 && p.y != 0);
	return Point(x / p.x, y / p.y);
}

Point Point::operator/(float f) const
{
	assert(f != 0);
	return Point(x / f, y / f);
}

Point & Point::operator=(const Point & p)
{
	x = p.x;
	y = p.y;
	return *this;
}

Point & Point::operator+=(const Point & p)
{
	x += p.x;
	y += p.y;
	return *this;
}

Point & Point::operator-=(const Point & p)
{
	x -= p.x;
	y -= p.y;
	return *this;
}

Point & Point::operator*=(const Point & p)
{
	x *= p.x;
	y *= p.y;
	return *this;
}

Point & Point::operator/=(const Point & p)
{
	x /= p.x;
	y /= p.y;
	return *this;
}

bool Point::operator==(const Point & p)
{
	return ((fabs(x - p.x) < EPSILON) && (fabs(y - p.y) < EPSILON));
}

bool Point::operator!=(const Point & p)
{
	return !operator==(p);
}

//ostream & operator<<(ostream & os, const Point & p)
//{
//	os << '(' << p.x << ',' << p.y << ')';
//	return os;
//}
