#ifndef CASE_DATA_H
#define CASE_DATA_H

#include "Shape.h"
#include <memory>

#include <d3dx11.h>

class CaseData
{
public:
	CaseData();
	~CaseData();

	std::shared_ptr<DamageZonePolygon> GetDZP() const { return DZP; }
	std::shared_ptr<MyPolygon> GetPolygon(int index) const { return polygons[index]; }
	int GetPolygonsCnt() const { return polygons.size(); }

	void CreateDamageZonePolygon(const DamageZoneInfo& info);
	void CreatePolygon(const vector<Point>& vertices);

	void CreateBuffers(ID3D11Device* device);
	void Draw(ID3D11DeviceContext* dc);

private:
	CaseData(const CaseData& other);
	CaseData& operator=(const CaseData& other);

private:
	std::shared_ptr<DamageZonePolygon> DZP;
	vector<std::shared_ptr<MyPolygon>> polygons;

};


#endif // !CASE_DATA_H
