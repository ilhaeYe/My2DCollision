#include "CaseData.h"

CaseData::CaseData()
{
}

CaseData::~CaseData()
{
	SafeDelete(DZP);
	
	for (vector<MyPolygon*>::reverse_iterator rev_it = polygons.rbegin(); rev_it != polygons.rend(); rev_it++)
		SafeDelete((*rev_it));
	polygons.clear();

}

void CaseData::CreateDamageZonePolygon(const DamageZoneInfo & info)
{
	DZP = new DamageZonePolygon(info);
}

void CaseData::CreatePolygon(const vector<Point>& vertices)
{
	polygons.push_back(new MyPolygon(vertices));
}

