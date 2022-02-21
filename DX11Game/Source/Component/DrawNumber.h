//=============================================================================
// Number.h
//=============================================================================
// Author  ���� ���V
//=============================================================================
#pragma once

#include <Renderer/Polygon/CPolygon.h>

//=============================================================================
// 
// �������O���
// 
//=============================================================================
namespace
{
	const auto Number = L"data/texture/UI/StageNumber.png";
}

//=============================================================================
// 
// �N���X��`
// 
//=============================================================================
class CNumber
{
public:
	CNumber();
	~CNumber() = default;

	CPolygon& GetPolygon() { return m_Polygon; }

	void Init(const wchar_t* FileName = Number);
	void Uninit();
	void Update();
	void Draw(int Number, XMFLOAT2 pos);

private:
	CPolygon m_Polygon;
	int m_nNumber;
	XMFLOAT2 m_Pos;
};