#ifndef UT_H
#define UT_H

#include "Point.h"
#include <iostream>
#include <memory>
#include <vector>
//#include <Windows.h>

class Point;

#define SafeDelete(x) { if(x){ delete x; x= NULL; } }
//#define UINT unsigned int

const float INFI = FLT_MAX;
const float Pi = 3.1415926535f;

// aabb
struct AABB
{
	Point maxP;
	Point minP;
	AABB(Point _max, Point _min) : maxP(_max), minP(_min) {};

};

namespace UT
{
	AABB GetAABB(std::vector<Point> vertices);
	Point GetMaxPoint(const Point& p1, const Point& p2);
	Point GetMinPoint(const Point& p1, const Point& p2);

	// 2차원 한정 
	float GetLength(const Point& p);
	Point GetUnitVector(const Point& p);
	Point GetNormalVector(const Point& p);
	float DotVector(const Point& p1, const Point& p2);
//	Point CrossVector(const Point& p1, const Point& p2);

}

//CRITICAL_SECTION    g_cs;
//class Lock
//{
//public:
//	inline Lock() { EnterCriticalSection(&g_cs); }
//	inline ~Lock() { LeaveCriticalSection(&g_cs); }
//};


#endif // !UT_H


