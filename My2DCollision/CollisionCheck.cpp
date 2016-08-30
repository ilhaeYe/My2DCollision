#include "CollisionCheck.h"

bool AABBCollisionCheck(const Shape* s1, const Shape* s2)
{
	return AABBCollisionCheck(s1->GetAABB(), s2->GetAABB());
}

bool AABBCollisionCheck(const AABB& aabb1, const AABB& aabb2)
{
	return !(IsGreaterPoint(aabb1.minP,aabb2.maxP) || IsGreaterPoint(aabb2.minP, aabb1.maxP));
}

bool IsGreaterPoint(const Point & p1, const Point & p2)
{
	return (p1.GetX() >= p2.GetX()) || (p1.GetY() >= p2.GetY());
}

bool SATCollisionCheck(const DamageZonePolygon * dzp, const MyPolygon * p)
{
	for (UINT i = 0; i < dzp->GetPlygonsSize(); i++)
		if (SATCollisionCheck(p, dzp->GetPolygon(i))) return true;
	for (UINT i = 0; i < dzp->GetCirclesSize(); i++)
		if (SATCollisionCheck(p, dzp->GetCircle(i))) return true;

	return false;
}

bool SATCollisionCheck(const MyPolygon* p1, const MyPolygon* p2)
{
	return SATCollisionCheck(p1->GetVertices(), p2->GetVertices());
}
//
bool SATCollisionCheck(const MyPolygon* p, const Circle * c)
{
	// get circle's axis
	Point minAxisVec(INFI, INFI);
	Point center(c->GetCenter());
	float radius = c->GetRadius();
	vector<Point> vertices = p->GetVertices();
	for (vector<Point>::iterator i = vertices.begin(); i != vertices.end(); i++)
	{
		Point gapVec((*i) - center);
		minAxisVec = UT::GetMinPoint(minAxisVec, gapVec);
	}
	minAxisVec = UT::GetUnitVector(minAxisVec);

	// get polygon's axis
	vector<Point> axisVector = UT::GetEdgesVector(vertices);
	// add circle's axis
	axisVector.push_back(minAxisVec);

	for (vector<Point>::iterator i = axisVector.begin(); i != axisVector.end(); i++)
	{
		AABB aabb1 = UT::GetAABBFromVerticesAndAxis(vertices, (*i));
		AABB aabb2 = UT::GetAABBFromCircleAndAxis(center, radius, (*i));
		if (AABBCollisionCheck(aabb1, aabb2) == false) return false;
	}

	return true;
}

bool SATCollisionCheck(const Circle * c1, const Circle * c2)
{
	float r1 = c1->GetRadius();
	float r2 = c2->GetRadius();
	float d = UT::GetLength(c2->GetCenter() - c1->GetCenter());
	return (r1 + r2 > d);
}

bool SATCollisionCheck(const vector<Point>& v1, const vector<Point>& v2)
{
	vector<Point> edgesVector1 = UT::GetEdgesVector(v1);
	vector<Point> edgesVector2 = UT::GetEdgesVector(v2);

	vector<Point> edgesVector;
	edgesVector.insert(edgesVector.end(), edgesVector1.begin(), edgesVector1.end());
	edgesVector.insert(edgesVector.end(), edgesVector2.begin(), edgesVector2.end());

	for (vector<Point>::iterator i = edgesVector.begin(); i != edgesVector.end(); i++)
	{
		AABB aabb1 = UT::GetAABBFromVerticesAndAxis(v1, UT::GetUnitVector((*i)));
		AABB aabb2 = UT::GetAABBFromVerticesAndAxis(v2, UT::GetUnitVector((*i)));
		if (AABBCollisionCheck(aabb1, aabb2) == false) return false;
	}

	return true;
}
