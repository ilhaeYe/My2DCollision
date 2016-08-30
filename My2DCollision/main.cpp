/*
CPP로 구현해 본 나만의 충돌 감지 테스트

Point 구현

Shape 부모 클래스
ㄴ Polygon 다각형 ( 시계방향 감기 )
ㄴ Sphere 원

DamageZone 특정 충돌 지역

AABB Collision 구현
SAT Collision 구현 (separate axis theorem collision)

*/

#include <iostream>
#include <memory>

#include "CasesDataHolder.h"
#include "CollisionCheck.h"

#include <vld.h>

using namespace std;

enum COLLISION_TYPE
{
	COLLISION_TYPE_NONE,
	COLLISION_TYPE_AABB,
	COLLISION_TYPE_SAT,
	COLLISION_TYPE_BOTH
};

void CollisionCheckOutPut(CasesDataHolder& cdh, const wchar_t* filePath, COLLISION_TYPE type);
void OutputData(const vector<UINT>& v);

int main()
{
	CasesDataHolder cdh;

	CollisionCheckOutPut(cdh, L"input1.txt", COLLISION_TYPE_BOTH);
	CollisionCheckOutPut(cdh, L"input2.txt", COLLISION_TYPE_BOTH);
	CollisionCheckOutPut(cdh, L"input3.txt", COLLISION_TYPE_BOTH);
//	CollisionCheckOutPut(cdh, L"input4.txt", COLLISION_TYPE_BOTH);
//	CollisionCheckOutPut(cdh, L"input5.txt", COLLISION_TYPE_BOTH);

	return 0;
}

void CollisionCheckOutPut(CasesDataHolder& cdh, const wchar_t* filePath, COLLISION_TYPE type)
{
	if (type == COLLISION_TYPE_NONE) return;

	cdh.ClearCasesData();

	vector<UINT> aabbCntList;
	vector<UINT> satCntList;
	bool bAABB = false;
	bool bSAT = false;
	if ((type == COLLISION_TYPE::COLLISION_TYPE_AABB || type == COLLISION_TYPE::COLLISION_TYPE_BOTH)) bAABB = true;
	if ((type == COLLISION_TYPE::COLLISION_TYPE_SAT || type == COLLISION_TYPE::COLLISION_TYPE_BOTH)) bSAT = true;

	cdh.ReadFilePath(filePath);
	wcout << endl << L"-----------------" << filePath << L"-----------------" << endl;
	for (UINT i = 0; i < cdh.GetCaseCnt(); i++)
	{
		UINT aabbCnt = 0;
		UINT satCnt = 0;
		for (UINT j = 0; j < cdh.GetCaseData(i)->GetPolygonsCnt(); j++)
		{
			if (bAABB &&
				AABBCollisionCheck(cdh.GetCaseData(i)->GetDZP(), cdh.GetCaseData(i)->GetPolygon(j))) aabbCnt++;
			if (bSAT &&
				SATCollisionCheck(cdh.GetCaseData(i)->GetDZP(), cdh.GetCaseData(i)->GetPolygon(j))) satCnt++;
		}
		aabbCntList.push_back(aabbCnt);
		satCntList.push_back(satCnt);
	}

	if (bAABB) { cout << endl << "-----------------AABB-----------------" << endl; OutputData(aabbCntList); }
	if (bSAT) { cout << endl << "-----------------SAT-----------------" << endl; OutputData(satCntList); }

}

void OutputData(const vector<UINT>& v)
{
	UINT index = 0;
	for (vector<UINT>::const_iterator ci = v.cbegin(); ci != v.cend(); ci++, index++)
		cout << "CASE " << index << " :: " << (*ci) << endl;
		
}
