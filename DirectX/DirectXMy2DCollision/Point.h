#ifndef POINT_H
#define POINT_H

#include <assert.h>
#include <math.h>
//#include <iostream>

using namespace std;
const float EPSILON = 0.00001f;

// my point class
class Point
{
public:
	Point();
	Point(float _x, float _y);
	Point(const Point& p);
	~Point();

	Point operator+(const Point& p) const;
	Point operator+(float f) const;
	Point operator-(const Point& p) const;
	Point operator-(float f) const;
	Point operator*(const Point& p) const;
	Point operator*(float f) const;
	Point operator/(const Point& p) const;
	Point operator/(float f) const;

	Point& operator=(const Point& p);

	Point& operator+=(const Point& p);
	Point& operator-=(const Point& p);
	Point& operator*=(const Point& p);
	Point& operator/=(const Point& p);

	bool operator==(const Point& p);
	bool operator!=(const Point& p);

	float GetX() const { return x; };
	float GetY() const { return y; };

	void SetX(float _x) { x = _x; };
	void SetY(float _y) { y = _y; };

	// for debug
//	friend ostream& operator<<(ostream& os, const Point& p);

private:
	float x;
	float y;
};

#endif // !POINT_H
