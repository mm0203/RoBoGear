//=============================================================================
// InstructionsScreen.h
//=============================================================================
// Author  ���� ���V
//=============================================================================
#pragma once

#include <Manager/BaseTexture.h>
#include <Renderer/Polygon/CPolygon.h>

//=============================================================================
// 
// �N���X��`
// 
//=============================================================================
class CInstructionsScreen : public CBaseTexture
{
public:
	CInstructionsScreen() = default;
	~CInstructionsScreen() = default;

	void Init()   override;
	void Uninit() override;
	void Update() override;
	void Draw()   override;

	// �y�[�W�؂�ւ����̈ړ���
	void PageMove(float& move);

private:
	std::vector<CPolygon> m_Polygons;
};

