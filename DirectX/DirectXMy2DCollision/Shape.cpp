#include "Shape.h"

// Shape

Shape::Shape() : type(SHAPE_TYPE::SHAPE_TYPE_NONE)
{
}

Shape::~Shape()
{
}

// Polygon

MyPolygon::MyPolygon()
{
	type = SHAPE_TYPE::SHAPE_TYPE_POLYGON;

}

MyPolygon::MyPolygon(const MyPolygon  & other)
{
	cout << "MyPolygon Copy Construct" << endl;
	vertices = other.vertices;
	boundary = other.boundary;
	type = other.type;
}

MyPolygon::MyPolygon(vector<Point> _vertices) : vertices(_vertices)
{
	type = SHAPE_TYPE::SHAPE_TYPE_POLYGON;
	Init();
}

MyPolygon ::~MyPolygon()
{
	ReleaseCOM(vb);
	ReleaseCOM(ib);
}

void MyPolygon::CreateBuffers(ID3D11Device * device)
{
	Point cp = (boundary[0].maxP + boundary[0].minP) *0.5f;
	
	vector<Vertex::PosColor> v(vertices.size() + 1);
	v[0].Pos = XMFLOAT3(cp.GetX(), 0.0f, cp.GetY());
	v[0].Color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	for (int i = 1; i < vertices.size() + 1; i++)
	{
		v[i].Pos = XMFLOAT3(vertices[i - 1].GetX(), 0.0f, vertices[i - 1].GetY());
		v[i].Color = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
	}
	
	vertexStride = sizeof(Vertex::PosColor);
	
	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(Vertex::PosColor) * v.size();
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;
	
	D3D11_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = &v[0];
	
	HR(device->CreateBuffer(&vbd, &vinitData, &vb));
	
	vector<UINT> indices;
	for (UINT i = 0; i < vertices.size(); i++)
	{
		indices.push_back(0);
		indices.push_back(i+1);
		indices.push_back((i == vertices.size()-1) ? 1 : i+2);
	}
	
	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(UINT) * indices.size();
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;
	
	D3D11_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = &indices[0];
	
	HR(device->CreateBuffer(&ibd, &iinitData, &ib));
		
	indicesCnt = indices.size();
}

void MyPolygon::Draw(ID3D11DeviceContext * dc)
{
	UINT offset = 0;

	dc->IASetVertexBuffers(0, 1, &vb, &vertexStride, &offset);
	dc->IASetIndexBuffer(ib, DXGI_FORMAT_R32_UINT, 0);

	dc->DrawIndexed(indicesCnt, 0, 0);
}

void MyPolygon::Init()
{
	CalcBoundary();
	Sort();
}

void MyPolygon::CalcBoundary()
{
	boundary.clear();
	boundary.push_back(AABB(UT::GetAABB(vertices)));
	//AABB aabb(Point(-INFI, -INFI), Point(INFI, INFI));
	//boundary.push_back(aabb);
	//
	//for (vector<Point>::iterator i = vertices.begin(); i != vertices.end(); i++)
	//{
	//	boundary[0].maxP = UT::GetMaxPoint(boundary[0].maxP, (*i));
	//	boundary[0].minP = UT::GetMinPoint(boundary[0].minP, (*i));
	//}
}

void MyPolygon::Sort()
{
	Point cp;
	cp = (boundary[0].maxP + boundary[0].minP) * 0.5;

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

Circle::Circle()
{
	type = SHAPE_TYPE::SHAPE_TYPE_CIRCLE;
	center = Point();
	radius = 0.0f;
}

Circle::Circle(const Circle & other)
{
	center = other.center;
	radius = other.radius;
	boundary = other.boundary;
	type = other.type;
}

Circle::Circle(Point _center, float _radius) : center(_center), radius(_radius)
{
	type = SHAPE_TYPE::SHAPE_TYPE_CIRCLE;
	CalcBoundary();
}

Circle::~Circle()
{
	ReleaseCOM(vb);
	ReleaseCOM(ib);
}

void Circle::Draw(ID3D11DeviceContext * dc)
{
	UINT offset = 0;

	dc->IASetVertexBuffers(0, 1, &vb, &vertexStride, &offset);
	dc->IASetIndexBuffer(ib, DXGI_FORMAT_R32_UINT, 0);

	dc->DrawIndexed(indicesCnt, 0, 0);
}

void Circle::CreateBuffers(ID3D11Device * device)
{
	vector<Vertex::PosColor> v;

	Vertex::PosColor cp;
	ZeroMemory(&cp, sizeof(Vertex::PosColor));
	cp.Pos = XMFLOAT3(center.GetX(), 0.0f, center.GetY());
	cp.Color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	
	v.push_back(cp);
	
	UINT sliceCount = 10;
	float thetaStep = 2.0f*XM_PI / sliceCount;
	
	for (UINT i = 0; i <= sliceCount; i++)
	{
		float theta = thetaStep * i;
			
		Vertex::PosColor p;
		ZeroMemory(&p, sizeof(Vertex::PosColor));
		
		p.Pos.x = cp.Pos.x + sinf(theta) * radius;
		p.Pos.z = cp.Pos.z + cosf(theta) * radius;
		p.Color = XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f);

		v.push_back(p);
	}
		
	vertexStride = sizeof(Vertex::PosColor);
	
	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(Vertex::PosColor) * v.size();
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;
	
	D3D11_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = &v[0];
	
	HR(device->CreateBuffer(&vbd, &vinitData, &vb));
	
	
	vector<UINT> indices;
	for (UINT i = 1; i <= sliceCount; i++)
	{
		indices.push_back(0);
		indices.push_back(i);
		indices.push_back(i + 1);
	}
	
	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(UINT) * indices.size();
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;
	
	D3D11_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = &indices[0];
	
	HR(device->CreateBuffer(&ibd, &iinitData, &ib));
	
	indicesCnt = indices.size();
	
}

void Circle::Init()
{
	CalcBoundary();
}

void Circle::CalcBoundary()
{
	boundary.clear();
	boundary.push_back(AABB(Point(center + radius), Point(center - radius)));
}

DamageZonePolygon::DamageZonePolygon()
{
	type = SHAPE_TYPE::SHAPE_TYPE_DAMAGEZONE;

}

DamageZonePolygon::DamageZonePolygon(const DamageZoneInfo & info)
{
	type = SHAPE_TYPE::SHAPE_TYPE_DAMAGEZONE;
	CreateDamageZoneData(info);
}

DamageZonePolygon::~DamageZonePolygon()
{
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
		circles.push_back(Circle(info.vertices[i], info.radius));
		
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

		polygons.push_back(MyPolygon(vertices));
	}
	CalcBoundary();
}

void DamageZonePolygon::Draw(ID3D11DeviceContext * dc)
{
	for (UINT i = 0; i < polygons.size(); i++)
		polygons[i].Draw(dc);
	for (UINT i = 0; i < circles.size(); i++)
		circles[i].Draw(dc);
}

void DamageZonePolygon::CreateBuffers(ID3D11Device * device)
{
	for (UINT i = 0; i < polygons.size(); i++)
		polygons[i].CreateBuffers(device);
	for (UINT i = 0; i < circles.size(); i++)
		circles[i].CreateBuffers(device);
}

void DamageZonePolygon::CalcBoundary()
{
	boundary.clear();
	// circles
	for (UINT i = 0; i < circles.size(); i++)
	{
		vector<AABB> source(circles[i].GetAABB());
		boundary.insert(boundary.end(), source.begin(), source.end());
	}
	// polygons
	for (UINT i = 0; i < polygons.size(); i++)
	{
		vector<AABB> source(polygons[i].GetAABB());
		boundary.insert(boundary.end(), source.begin(), source.end());
	}
}
