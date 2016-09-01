#ifndef CASES_DATA_HOLDER_H
#define CASES_DATA_HOLDER_H

#include "CaseData.h"
#include <fstream>
#include <memory>

// graphic
#include <d3dx11.h>

class CasesDataHolder
{
public:
	CasesDataHolder();
	~CasesDataHolder();

	const std::shared_ptr<CaseData> GetCaseData(int index) const { return cases[index]; }
	UINT GetCaseCnt() const { return cases.size(); }

	void ReadFilePath(ID3D11Device* _device, wchar_t* filePath);
	void CreateBuffers(ID3D11Device* device);
	void DrawCase(ID3D11DeviceContext* dc, int index);

private:
	CasesDataHolder(const CasesDataHolder& other);
	CasesDataHolder& operator=(const CasesDataHolder& other);

	void ReadDamageZoneData(ifstream& fin, UINT caseIndex);
	void ReadPolygonData(ifstream& fin, UINT caseIndex);

private:
	vector<std::shared_ptr<CaseData>> cases;

};

#endif // !CASES_DATA_HOLDER_H
