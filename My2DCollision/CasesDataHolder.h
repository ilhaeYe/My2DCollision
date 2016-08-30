#ifndef CASES_DATA_HOLDER_H
#define CASES_DATA_HOLDER_H

#include "CaseData.h"
#include <fstream>
#include <memory>

class CasesDataHolder
{
public:
	CasesDataHolder();
	~CasesDataHolder();

	CaseData* GetCaseData(int index) const { return cases[index]; }
	UINT GetCaseCnt() const { return cases.size(); }

	void ReadFilePath(const wchar_t* filePath);
	void ClearCasesData();

private:
	CasesDataHolder(const CasesDataHolder& other);
	CasesDataHolder& operator=(const CasesDataHolder& other);

	void ReadDamageZoneData(ifstream& fin, UINT caseIndex);
	void ReadPolygonData(ifstream& fin, UINT caseIndex);

private:
	vector<CaseData*> cases;

};

#endif // !CASES_DATA_HOLDER_H
