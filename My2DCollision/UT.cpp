#include "UT.h"

AABB UT::GetAABB(const vector<Point>& vertices)
{
	Point maxP(-INFI, -INFI);
	Point minP(INFI, INFI);

	for (vector<Point>::const_iterator ci = vertices.begin(); ci != vertices.end(); ci++)
	{
		maxP = GetMaxPoint(maxP, (*ci));
		minP = GetMinPoint(minP, (*ci));
	}

	AABB result;
	result.maxP = maxP;
	result.minP = minP;
	return result;
}

AABB UT::GetAABBFromVerticesAndAxis(const vector<Point>& vertices, const Point & axisVec)
{
	return UT::GetAABB(GetProjectedVertices(vertices, axisVec));
}

AABB UT::GetAABBFromCircleAndAxis(const Point & center, float radius, const Point & axisVec)
{
	Point dir = UT::GetUnitVector(axisVec) * radius;
	
	std::vector<Point> vertices;
	vertices.push_back(Point(center + dir));
	vertices.push_back(Point(center - dir));
	
	return UT::GetAABB(GetProjectedVertices(vertices, axisVec));
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

vector<Point> UT::GetProjectedVertices(const vector<Point>& vertices, const Point & axisVec)
{
	vector<Point> projectedVertices;
	for (vector<Point>::const_iterator ci = vertices.begin(); ci != vertices.end(); ci++)
		projectedVertices.push_back(UT::GetProjectedVertex((*ci), axisVec));

	return projectedVertices;
}

Point UT::GetProjectedVertex(const Point & p, const Point & axisVec)
{
	float dotValue = UT::DotVector(p, axisVec);

	return Point(dotValue, dotValue);
}

vector<Point> UT::GetEdgesVector(const vector<Point>& v)
{
	vector<Point> edges;
	UINT size = v.size();
	for (UINT i = 0; i < size; i++)
	{
		UINT current = i;
		UINT next = ((i + 1) < size) ? i + 1 : 0;
		edges.push_back(v[next] - v[current]);
	}
	return edges;
}