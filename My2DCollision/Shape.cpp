#include "Shape.h"

// Shape

Shape::Shape() : type(SHAPE_TYPE::SHAPE_TYPE_NONE)
{
}

Shape::~Shape()
{
}

// Polygon

//MyPolygon::MyPolygon()
//{
//	type = SHAPE_TYPE::SHAPE_TYPE_POLYGON;
//
//}

//MyPolygon::MyPolygon(const MyPolygon  & other)
//{
////	cout << "MyPolygon Copy Construct" << endl;
//	vertices = other.vertices;
//	boundary = other.boundary;
//	type = other.type;
//}

MyPolygon::MyPolygon(vector<Point> _vertices) : vertices(_vertices)
{
	type = SHAPE_TYPE::SHAPE_TYPE_POLYGON;
	Init();
}

MyPolygon ::~MyPolygon()
{
}


void MyPolygon::Init()
{
	CalcBoundary();
	Sort();
}

void MyPolygon::CalcBoundary()
{
	boundary = UT::GetAABB(vertices);
}

void MyPolygon::Sort()
{
	Point cp;
	cp = (boundary.maxP + boundary.minP) * 0.5;

	typedef pair<double, Point> myPair;
	map<double, Point> m;
	for (size_t i = 0; i < vertices.size(); i++)
	{
		Point p = vertices.at(i);
		double r = atan2(p.GetY() - cp.GetY(), p.GetX() - cp.GetX());

		m.insert(myPair(r, p));
	}
	vertices.clear();
	for (map<double, Point>::reverse_iterator rev_it = m.rbegin(); rev_it != m.rend(); rev_it++)
		vertices.push_back((*rev_it).second);

}

// Circle

//Circle::Circle()
//{
//	type = SHAPE_TYPE::SHAPE_TYPE_CIRCLE;
//	center = Point();
//	radius = 0.0f;
//}

//Circle::Circle(const Circle & other)
//{
//	center = other.center;
//	radius = other.radius;
//	boundary = other.boundary;
//	type = other.type;
//}

Circle::Circle(Point _center, float _radius) : center(_center), radius(_radius)
{
	type = SHAPE_TYPE::SHAPE_TYPE_CIRCLE;
	CalcBoundary();
}

Circle::~Circle()
{
}


void Circle::Init()
{
	CalcBoundary();
}

void Circle::CalcBoundary()
{
	boundary.maxP = Point(center + radius);
	boundary.minP = Point(center - radius);
}

//DamageZonePolygon::DamageZonePolygon()
//{
//	type = SHAPE_TYPE::SHAPE_TYPE_DAMAGEZONE;
//
//}

DamageZonePolygon::DamageZonePolygon(const DamageZoneInfo & info)
{
	type = SHAPE_TYPE::SHAPE_TYPE_DAMAGEZONE;
	CreateDamageZoneData(info);
}

DamageZonePolygon::~DamageZonePolygon()
{
	for (vector<MyPolygon*>::reverse_iterator rev_it = polygons.rbegin(); rev_it != polygons.rend(); rev_it++)
		SafeDelete((*rev_it));
	polygons.clear();

	for (vector<Circle*>::reverse_iterator rev_it = circles.rbegin(); rev_it != circles.rend(); rev_it++)
		SafeDelete((*rev_it));
	circles.clear();
}

//
// cc+nv*-------------*nc+nv
//      |     ¡ènv     |
//    cc*     v->     *nc
//      |             |
// cc-nv*-------------*nc-nv
//
void DamageZonePolygon::CreateDamageZoneData(const DamageZoneInfo & info)
{
	UINT size = info.vertices.size();
	for (UINT i = 0; i < size; i++)
	{
		// circle
		circles.push_back(new Circle(info.vertices[i], info.radius));
		
		// polygon
		vector<Point> vertices;
		UINT currentIndex = i;
		UINT nextIndex = (i + 1 < size) ? i + 1 : 0;
		Point currentCenter = info.vertices[currentIndex];
		Point nextCenter = info.vertices[nextIndex];

		Point v = UT::GetUnitVector((nextCenter - currentCenter));
		Point nv = UT::GetNormalVector(v) * info.radius;

		vertices.push_back(Point(currentCenter + nv));
		vertices.push_back(Point(nextCenter + nv));
		vertices.push_back(Point(nextCenter - nv));
		vertices.push_back(Point(currentCenter - nv));

		polygons.push_back(new MyPolygon(vertices));
	}
	CalcBoundary();
}

void DamageZonePolygon::CalcBoundary()
{
	boundary.maxP = Point(-INFI, -INFI);
	boundary.minP = Point(INFI, INFI);

	for (vector<MyPolygon*>::iterator i = polygons.begin(); i != polygons.end(); i++)
	{
		 AABB aabb = (*i)->GetAABB();
		 boundary.maxP = UT::GetMaxPoint(boundary.maxP, aabb.maxP);
		 boundary.minP = UT::GetMinPoint(boundary.minP, aabb.minP);
	}

	for (vector<Circle*>::iterator i = circles.begin(); i != circles.end(); i++)
	{
		AABB aabb = (*i)->GetAABB();
		boundary.maxP = UT::GetMaxPoint(boundary.maxP, aabb.maxP);
		boundary.minP = UT::GetMinPoint(boundary.minP, aabb.minP);
	}

}
