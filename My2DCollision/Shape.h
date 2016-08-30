#ifndef SHAPE_H
#define SHAPE_H

#include "UT.h"
#include <map>

using namespace std;

enum SHAPE_TYPE
{
	SHAPE_TYPE_NONE,
	SHAPE_TYPE_POLYGON,
	SHAPE_TYPE_CIRCLE,
	SHAPE_TYPE_DAMAGEZONE
};
// shape
class Shape
{
public:
	Shape();
	virtual ~Shape();
	
	SHAPE_TYPE GetType() const { return type; }
	AABB GetAABB() const { return boundary; }
protected:
	virtual void CalcBoundary() = 0;

protected:
	SHAPE_TYPE type;
	AABB boundary;

private:
	Shape(const Shape& other);
	Shape& operator=(const Shape& other);

};

// polygon
class MyPolygon : public Shape
{
public:
	MyPolygon(vector<Point> _vertices);
	virtual ~MyPolygon();

	vector<Point> GetVertices() const { return vertices; };

protected:
	virtual void Init();
	virtual void CalcBoundary();
	virtual void Sort();
	
private:
	MyPolygon(const MyPolygon & other);
	MyPolygon & operator=(const MyPolygon & other);

private:
	vector<Point> vertices;

};

// circle
class Circle : public Shape
{
public:
	Circle(Point _center, float _radius);
	virtual ~Circle();

	Point GetCenter() const { return center; }
	float GetRadius() const { return radius; }

protected:
	virtual void Init();
	virtual void CalcBoundary();

private:
	Circle(const Circle& other);
	Circle& operator=(const Circle& other);

private:
	Point center;
	float radius;

};

// DamageZonePolygon
struct DamageZoneInfo
{
	float radius;
	vector<Point> vertices;
};

class DamageZonePolygon : public Shape
{
public:
	DamageZonePolygon(const DamageZoneInfo& info);
	virtual ~DamageZonePolygon();

	MyPolygon* GetPolygon(UINT index) const { return polygons[index]; }
	UINT GetPlygonsSize() const { return polygons.size(); }
	Circle* GetCircle(UINT index) const { return circles[index]; }
	UINT GetCirclesSize() const { return circles.size(); }

protected:
	virtual void CalcBoundary();

private:
	DamageZonePolygon(const DamageZonePolygon& other);
	DamageZonePolygon& operator=(const DamageZonePolygon& other);

	void CreateDamageZoneData(const DamageZoneInfo& info);

private:
	vector<MyPolygon*> polygons;
	vector<Circle*> circles;

};


#endif // !SHAPE_H
