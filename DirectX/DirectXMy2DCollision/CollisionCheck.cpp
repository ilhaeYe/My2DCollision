//#include "CollisionCheck.h"
//
//bool AABBCollisionCheck(const Shape & s1, const Shape & s2)
//{
//	return AABBCollisionCheck(s1.GetAABB(), s2.GetAABB());
//}
//
//bool AABBCollisionCheck(vector<AABB> v1, vector<AABB> v2)
//{
//	bool result = false;
//	for (UINT i = 0; i < v1.size(); i++)
//	{
//		for (UINT j = 0; j < v2.size(); j++)
//		{
//			result = AABBCollisionCheck(v1[i], v2[j]);
//		}
//	}
//	return result;
//}
//
//bool AABBCollisionCheck(AABB aabb1, AABB aabb2)
//{
//	return !(IsGreaterPoint(aabb1.minP, aabb2.maxP) || IsGreaterPoint(aabb2.minP, aabb1.maxP));
//}
//
//bool IsGreaterPoint(const Point & p1, const Point & p2)
//{
//	return (p1.GetX() >= p2.GetX()) || (p1.GetY() >= p2.GetY());
//}

#include "CollisionCheck.h"

bool AABBCollisionCheck(std::shared_ptr<Shape> s1, std::shared_ptr<Shape> s2)
{
	return AABBCollisionCheck(s1->GetAABB(), s2->GetAABB());
}

bool AABBCollisionCheck(vector<AABB> v1, vector<AABB> v2)
{
	for (UINT i = 0; i < v1.size(); i++)
	{
		for (UINT j = 0; j < v2.size(); j++)
		{
			if (AABBCollisionCheck(v1[i], v2[j])) return true;
		}
	}
	return false;
}

bool AABBCollisionCheck(AABB aabb1, AABB aabb2)
{
	return !(IsGreaterPoint(aabb1.minP,aabb2.maxP) || IsGreaterPoint(aabb2.minP, aabb1.maxP));
}

bool IsGreaterPoint(const Point & p1, const Point & p2)
{
	return (p1.GetX() >= p2.GetX()) || (p1.GetY() >= p2.GetY());
}

// SAT
bool SATCollisionCheck(std::shared_ptr<DamageZonePolygon> dzp, std::shared_ptr<MyPolygon> p)
{
	for (UINT i = 0; i < dzp->GetPolygons().size(); i++)
		if (SATCollisionCheck(p, dzp->GetPolygons()[i])) return true;

	// TODO 동그라미 SAT 감시 문제가 있는듯?
	for (UINT i = 0; i < dzp->GetCircles().size(); i++)
		if (SATCollisionCheck(p, dzp->GetCircles()[i])) return true;

//	for (vector<MyPolygon>::iterator i = dzp->GetPolygons().begin(); i != dzp->GetPolygons().end(); i++)
//		if (SATCollisionCheck(p, (*i))) return true;
//	for (vector<Circle>::iterator i = dzp->GetCircles().begin(); i != dzp->GetCircles().end(); i++)
//		if (SATCollisionCheck(p, (*i))) return true;
	return false;
}


bool SATCollisionCheck(std::shared_ptr<MyPolygon> p1, const MyPolygon & p2)
{
	return SATCollisionCheck(p1->GetVertices(), p2.GetVertices());
}

bool SATCollisionCheck(std::shared_ptr<MyPolygon> p, const Circle & c)
{
	// get circle's axis
	Point minVec(INFI, INFI);
	for (UINT i = 0; i < p->GetVertices().size(); i++)
	{
		Point gapVec(GetGapVector(p->GetVertices()[i], c.GetVertex()));
		minVec = UT::GetMinPoint(minVec, gapVec);
	}
	Point axisVec = UT::GetUnitVector(minVec);

	// get polygon's edge
	vector<Point> edgesVector = GetEdgesVector(p->GetVertices());
	// add circle's axis
	edgesVector.push_back(axisVec);

	for (vector<Point>::iterator i = edgesVector.begin(); i != edgesVector.end(); i++)
	{
		AABB aabb1 = GetAABB(p->GetVertices(), (*i));
		AABB aabb2 = GetAABB(c, (*i));
		if (AABBCollisionCheck(aabb1, aabb2) == false) return false;
	}

	return true;
}

Point GetGapVector(const Point& p1, const Point& p2)
{
	return Point(p2 - p1);
}

bool SATCollisionCheck(vector<Point> p1, vector<Point> p2)
{
	vector<Point> edgesVector1 = GetEdgesVector(p1);
	vector<Point> edgesVector2 = GetEdgesVector(p2);

	vector<Point> edgesVector;
	edgesVector.insert(edgesVector.end(), edgesVector1.begin(), edgesVector1.end());
	edgesVector.insert(edgesVector.end(), edgesVector2.begin(), edgesVector2.end());

	for (vector<Point>::iterator i = edgesVector.begin(); i != edgesVector.end(); i++)
		(*i) = UT::GetUnitVector((*i));

	for (UINT i = 0; i < edgesVector.size(); i++)
	{
		AABB aabb1 = GetAABB(p1, edgesVector[i]);
		AABB aabb2 = GetAABB(p2, edgesVector[i]);
		if (AABBCollisionCheck(aabb1, aabb2) == false) return false;
	}

	return true;
}

AABB GetAABB(vector<Point> vertices, const Point & axisVec)
{
	return UT::GetAABB(GetProjectedVertices(vertices, axisVec));
}

AABB GetAABB(const Circle& c, const Point& axisVec)
{
	//	float r = c.GetRadius();
	//	Point unitDirVector = UT::GetUnitVector(dirVector);
	//	Point dir = UT::getunitDirVector * r;

	Point dir = UT::GetUnitVector(axisVec) * c.GetRadius();

	std::vector<Point> vertices;
	vertices.push_back(Point(c.GetVertex() + dir));
	vertices.push_back(Point(c.GetVertex() - dir));

	//return UT::GetAABB(vertices);
	return UT::GetAABB(GetProjectedVertices(vertices, axisVec));
}

vector<Point> GetProjectedVertices(vector<Point> vertices, const Point& axisVector)
{
	vector<Point> projectedVertices;
	for (vector<Point>::iterator i = vertices.begin(); i != vertices.end(); i++)
	{
		float dotValue = UT::DotVector((*i), axisVector);
		Point projectedVertex(dotValue, dotValue);
		projectedVertices.push_back(projectedVertex);
	}
	return projectedVertices;
}

vector<Point> GetEdgesVector(const MyPolygon& p)	// vector를 파라미터로 넘길 경우 드는 비용과 참조자를 넘길 경우의 비용 차이는?
{
	vector<Point> edges;
	for (UINT i = 0; i < p.GetVertices().size(); i++)
	{
		UINT current = i;
		UINT next = (i + 1) % p.GetVertices().size();	// 삼항연산자, %연산자, if문 3가지 경우의 속도 차이는? 어떤걸 써야할까?
		Point edge = p.GetVertices()[next] - p.GetVertices()[current];
		edges.push_back(edge);
	}
	return edges;
}

// SAT
//
//bool SATCollisionCheck(const DamageZonePolygon & dzp, const Shape & shape)
//{
//	return false;
//}
//
//bool SATCollisionCheck(const MyPolygon & p1, const MyPolygon & p2)
//{
//	vector<Point> edgesVector1 = GetEdgesVector(p1);
//	vector<Point> edgesVector2 = GetEdgesVector(p2);
//
//	vector<Point> normalVectors = GetNormalVectors(edgesVector1, edgesVector2);
//	for (vector<Point>::iterator i = normalVectors.begin(); i != normalVectors.end(); i++)
//		(*i) = UT::GetUnitVector((*i));
//
//	for (UINT i = 0; i < normalVectors.size(); i++)
//	{
//		AABB aabb1 = GetAABB(p1.GetVertices(), normalVectors[i]);
//		AABB aabb2 = GetAABB(p2.GetVertices(), normalVectors[i]);
//		if (AABBCollisionCheck(aabb1, aabb2) == false) return false;
//	}
//
//	return true;
//}
//
//bool SATCollisionCheck(vector<Point> p1, vector<Point> p2)
//{
//	return false;
//}
//
//AABB GetAABB(vector<Point> vertices, const Point & normalVector)
//{
//	return UT::GetAABB(GetProjectedVertices(vertices, normalVector));
//}
//
//vector<Point> GetProjectedVertices(vector<Point> vertices, const Point& normalVector)
//{
//	vector<Point> projectedVertices;
//	for (vector<Point>::iterator i = vertices.begin(); i != vertices.end(); i++)
//	{
//		float dotValue = UT::DotVector((*i), normalVector);
//		Point projectedVertex(dotValue, dotValue);
//		projectedVertices.push_back(projectedVertex);
//	}
//	return projectedVertices;
//}
//
//vector<Point> GetEdgesVector(const MyPolygon& p)	// vector를 파라미터로 넘길 경우 드는 비용과 참조자를 넘길 경우의 비용 차이는?
//{
//	vector<Point> edges;
//	for (UINT i = 0; i < p.GetVertices().size(); i++)
//	{
//		UINT current = i;
//		UINT next = (i + 1) % p.GetVertices().size();	// 삼항연산자, %연산자, if문 3가지 경우의 속도 차이는? 어떤걸 써야할까?
//		Point edge = p.GetVertices()[next] - p.GetVertices()[current];
//		edges.push_back(edge);
//	}
//	return edges;
//}
//
//vector<Point> GetNormalVectors(vector<Point> edges1, vector<Point> edges2)
//{
//	vector<Point> returnVectors;
//	vector<Point> vectors1 = GetNormalVectors(edges1);
//	vector<Point> vectors2 = GetNormalVectors(edges2);
//	returnVectors.insert(returnVectors.end(), vectors1.begin(), vectors1.end());
//	returnVectors.insert(returnVectors.end(), vectors2.begin(), vectors2.end());
//	return returnVectors;
//}
//
//vector<Point> GetNormalVectors(vector<Point> edges)
//{
//	vector<Point> vectors;
//	for (UINT i = 0; i < edges.size(); i++)
//	{
//		vectors.push_back(UT::GetNormalVector(edges[i]));
//	}
//	return vectors;
//}



//
//bool SATCollisionCheck(std::shared_ptr<DamageZonePolygon> s1, std::shared_ptr<Shape> s2)
//{
//	return false;
//}
//
//bool SATCollisionCheck(std::shared_ptr<MyPolygon> p, std::shared_ptr<Circle> c)
//{
//	return false;
//}
//
//
//bool SATCollisionCheck(std::shared_ptr<MyPolygon> p1, std::shared_ptr<MyPolygon> p2)
//{
//	return SATCollisionCheck(p1->GetVertices(), p2->GetVertices());
//}



// TODO
// 다시 찬찬히 생각해서 고민해보자


//bool SATCollisionCheck(vector<Point> v1, vector<Point> v2)
//{
//	AABB aabb1 = GetSATAABB(v1);
//	AABB aabb2 = GetSATAABB(v2);
//
//	return AABBCollisionCheck(aabb1, aabb2);
//
//	// 엣지 가져옴
//	// 엣지의 노말벡터 구함
//	// 구한 노말벡터마다 각 엣지를 투영함
//	// 결과값 AABB를 겹치는지 확인함
//	// 겹치면 겹치는거고 아니면 아닌거고
//
//}
//
//bool SATCollisionCheck(const Point & p1, const Point & p2)
//{
//	return false;
//}
//
//AABB GetSATAABB(vector<Point> v)
//{
//	vector<Point> edges = GetEdges(v);
//	vector<Point> normalVectors = GetNormalVectors(edges);
//	//vector<Point> projectedEdges = GetProjectedEdges(edges, normalVectors);
//	return (UT::GetAABB(GetProjectedEdges(edges, normalVectors)));
//
//	//for (UINT i = 0; i < normalVectors.size(); i++)
//	//{
//	//	vector<Point> projectedEdges = GetProjectdEdges(edges, normalVectors[i]);
//	//}
//	//	AABB resultAABB1 = UT::GetAABB(projectedEdges1);
//
////	return AABB()
//}
//
//vector<Point> GetProjectedEdges(vector<Point> edges, vector<Point> normalVectors)
//{
//	vector<Point> projectedEdges;
//	for (UINT i = 0; i < normalVectors.size(); i++)
//	{
//		projectedEdges += GetProjectdEdges(edges, normalVectors[i]);
//	}
//
//	return projectedEdges;
//}
//
