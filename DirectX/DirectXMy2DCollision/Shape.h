#ifndef SHAPE_H
#define SHAPE_H

#include "UT.h"
//#include <vector>
#include <map>
//#include <memory>

#include <d3dx11.h>
#include "..\Vertex.h"

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
	vector<AABB> GetAABB() const { return boundary; }
protected:
	vector<AABB> boundary;
	SHAPE_TYPE type;

	virtual void CalcBoundary() = 0;
private:

};

// polygon
class MyPolygon : public Shape
{
public:
	MyPolygon();
	MyPolygon(const MyPolygon & other);
	MyPolygon(vector<Point> _vertices);
	virtual ~MyPolygon();

	vector<Point> GetVertices() const { return vertices; };

	void CreateBuffers(ID3D11Device* device);
	void Draw(ID3D11DeviceContext* dc);

protected:
	virtual void Init();
	virtual void CalcBoundary();
	virtual void Sort();
	
private:
	MyPolygon & operator=(const MyPolygon & other);

private:
	vector<Point> vertices;
	ID3D11Buffer* vb = 0;
	ID3D11Buffer* ib = 0;
	UINT vertexStride = 0;
	UINT indicesCnt = 0;

};

// circle
class Circle : public Shape
{
public:
	Circle();
	Circle(const Circle& other);
	Circle(Point _center, float _radius);
	virtual ~Circle();

	Point GetVertex() const { return center; }
	float GetRadius() const { return radius; }

	void Draw(ID3D11DeviceContext* dc);
	void CreateBuffers(ID3D11Device* device);

protected:
	virtual void Init();
	virtual void CalcBoundary();

private:
	Circle& operator=(const Circle& other);

private:
	Point center;
	float radius;
	ID3D11Buffer* vb = 0;
	ID3D11Buffer* ib = 0;
	UINT vertexStride = 0;
	UINT indicesCnt = 0;

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
	DamageZonePolygon();
	DamageZonePolygon(const DamageZoneInfo& info);
	virtual ~DamageZonePolygon();

	vector<MyPolygon> GetPolygons() const { return polygons; }
	UINT GetPlygonsSize() const { return polygons.size(); }
	vector<Circle> GetCircles() const { return circles; }
	UINT GetCirclesSize() const { return circles.size(); }

	void CreateDamageZoneData(const DamageZoneInfo& info);
	void Draw(ID3D11DeviceContext* dc);
	void CreateBuffers(ID3D11Device* device);

protected:
	virtual void CalcBoundary();

private:
	DamageZonePolygon(const DamageZonePolygon& other);
	DamageZonePolygon& operator=(const DamageZonePolygon& other);

private:
	vector<MyPolygon> polygons;
	vector<Circle> circles;


};


#endif // !SHAPE_H
