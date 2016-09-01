#include "CaseData.h"

CaseData::CaseData()
{
}

CaseData::~CaseData()
{
}

void CaseData::CreateDamageZonePolygon(const DamageZoneInfo & info)
{
	DZP = std::shared_ptr<DamageZonePolygon>(new DamageZonePolygon(info));
}

void CaseData::CreatePolygon(const vector<Point>& vertices)
{
	polygons.push_back(std::shared_ptr<MyPolygon>(new MyPolygon(vertices)));
}

void CaseData::CreateBuffers(ID3D11Device * device)
{
	for (unsigned int i = 0; i < polygons.size(); i++)
		polygons[i]->CreateBuffers(device);
	DZP->CreateBuffers(device);
}

void CaseData::Draw(ID3D11DeviceContext * dc)
{
	for (UINT i = 0; i < polygons.size(); i++)
		polygons[i]->Draw(dc);
	DZP->Draw(dc);
}

