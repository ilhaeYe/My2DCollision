#include "CasesDataHolder.h"

CasesDataHolder::CasesDataHolder()
{
}

CasesDataHolder::~CasesDataHolder()
{
}

void CasesDataHolder::ReadFilePath(ID3D11Device* _device, wchar_t * filePath)
{
	cases.clear();

	ifstream fin(filePath);
	UINT caseNum = 0;
	UINT polygonNum = 0;
	if (fin)
	{
		fin >> caseNum;
		for (UINT caseIndex = 0; caseIndex < caseNum; caseIndex++)
		{
			cases.push_back(std::shared_ptr<CaseData>(new CaseData()));
			ReadDamageZoneData(fin, caseIndex);
			fin >> polygonNum;
			for (UINT j = 0; j < polygonNum; j++)
			{
				ReadPolygonData(fin, caseIndex);
			}
		}
	}

}

void CasesDataHolder::CreateBuffers(ID3D11Device * device)
{
	for (unsigned int i = 0; i < cases.size(); i++)
	{
		cases[i]->CreateBuffers(device);
	}
}

void CasesDataHolder::DrawCase(ID3D11DeviceContext* dc, int index)
{
	cases[index]->Draw(dc);
}

void CasesDataHolder::ReadDamageZoneData(ifstream & fin, UINT caseIndex)
{
	DamageZoneInfo info;
	float r, x1, y1, x2, y2, x3, y3 = 0;
	fin >> r >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
	info.radius = r;
	info.vertices.push_back(Point(x1, y1));
	info.vertices.push_back(Point(x2, y2));
	info.vertices.push_back(Point(x3, y3));

	cases[caseIndex]->CreateDamageZonePolygon(info);
}

void CasesDataHolder::ReadPolygonData(ifstream & fin, UINT caseIndex)
{
	UINT vNum = 0;
	vector<Point> vertices;
	fin >> vNum;
	for (UINT i = 0; i < vNum; i++)
	{
		float x, y = 0;
		fin >> x >> y;
		Point p(x, y);
		vertices.push_back(p);
	}
	cases[caseIndex]->CreatePolygon(vertices);
}


