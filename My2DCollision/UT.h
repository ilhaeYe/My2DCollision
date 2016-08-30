#ifndef UT_H
#define UT_H

#include "Point.h"
#include <iostream>
#include <memory>
#include <vector>
//#include <Windows.h>

class Point;

#define SafeDelete(x) { if(x){ delete x; x= NULL; } }
#define UINT unsigned int

const float INFI = FLT_MAX;
const float Pi = 3.1415926535f;

using namespace std;

// aabb
struct AABB
{
	Point maxP;
	Point minP;
};

namespace UT
{
	AABB GetAABB(const vector<Point>& vertices);
	AABB GetAABBFromVerticesAndAxis(const vector<Point>& vertices, const Point& axisVec);
	AABB GetAABBFromCircleAndAxis(const Point& center, float radius, const Point& axisVec);
	Point GetMaxPoint(const Point& p1, const Point& p2);
	Point GetMinPoint(const Point& p1, const Point& p2);

	// 2차원 한정 
	float GetLength(const Point& p);
	Point GetUnitVector(const Point& p);
	Point GetNormalVector(const Point& p);
	float DotVector(const Point& p1, const Point& p2);
//	Point CrossVector(const Point& p1, const Point& p2);

	vector<Point> GetProjectedVertices(const vector<Point>& vertices, const Point& axisVec);
	Point GetProjectedVertex(const Point& p, const Point& axisVec);
	vector<Point> GetEdgesVector(const vector<Point>& v);

}

//CRITICAL_SECTION    g_cs;
//class Lock
//{
//public:
//	inline Lock() { EnterCriticalSection(&g_cs); }
//	inline ~Lock() { LeaveCriticalSection(&g_cs); }
//};


#endif // !UT_H


