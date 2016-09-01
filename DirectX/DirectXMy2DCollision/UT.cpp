#include "UT.h"

AABB UT::GetAABB(std::vector<Point> vertices)
{
	Point maxP(-INFI, -INFI);
	Point minP(INFI, INFI);
	
	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		maxP = GetMaxPoint(maxP, vertices[i]);
		minP = GetMinPoint(minP, vertices[i]);
	}
	return AABB(maxP, minP);
}

Point UT::GetMaxPoint(const Point & p1, const Point & p2)
{
	float maxX, maxY = -INFI;

	maxX = (p1.GetX() >= p2.GetX()) ? p1.GetX() : p2.GetX();
	maxY = (p1.GetY() >= p2.GetY()) ? p1.GetY() : p2.GetY();

	return Point(maxX, maxY);
}

Point UT::GetMinPoint(const Point & p1, const Point & p2)
{
	float minX, minY = +INFI;

	minX = (p1.GetX() <= p2.GetX()) ? p1.GetX() : p2.GetX();
	minY = (p1.GetY() <= p2.GetY()) ? p1.GetY() : p2.GetY();

	return Point(minX, minY);
}

float UT::GetLength(const Point & p)
{
	return sqrt(pow(p.GetX(), 2) + pow(p.GetY(), 2));
}

Point UT::GetUnitVector(const Point & p)
{
	return Point(p / GetLength(p));
}

Point UT::GetNormalVector(const Point & p)
{
	return Point(-p.GetY(), p.GetX());
}

float UT::DotVector(const Point & p1, const Point & p2)
{
	return (p1.GetX()*p2.GetX()) + (p1.GetY()*p2.GetY());
}
