#ifndef CASE_DATA_H
#define CASE_DATA_H

#include "Shape.h"
#include <memory>

class CaseData
{
public:
	CaseData();
	~CaseData();

	DamageZonePolygon* GetDZP() const { return DZP; }
	MyPolygon* GetPolygon(int index) const { return polygons[index]; }
	UINT GetPolygonsCnt() const { return polygons.size(); }

	void CreateDamageZonePolygon(const DamageZoneInfo& info);
	void CreatePolygon(const vector<Point>& vertices);

private:
	CaseData(const CaseData& other);
	CaseData& operator=(const CaseData& other);

private:
	DamageZonePolygon* DZP;
	vector<MyPolygon*> polygons;

};

#endif // !CASE_DATA_H
