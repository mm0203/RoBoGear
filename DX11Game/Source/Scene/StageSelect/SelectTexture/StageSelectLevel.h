//=============================================================================
// StageSelectLevel.h
//=============================================================================
// Author  ���� ���V
//=============================================================================
#pragma once

#include <Manager/BaseTexture.h>
#include <Renderer/Polygon/CPolygon.h>
#include <map>

//=============================================================================
// 
// �}�N����`
// 
//=============================================================================


//=============================================================================
// 
// �N���X��`
// 
//=============================================================================
class CStageSelectLevel : public CBaseTexture
{
public:
	CStageSelectLevel() = default;
	~CStageSelectLevel() = default;

	void Init()   override;
	void Uninit() override;
	void Update() override;
	void Draw()   override;

	// getter
	XMFLOAT2 GetLevelPos();
	XMFLOAT2 GetLevelSize();

private:
	std::vector<CPolygon> m_Polygons;

	// �e�X�e�[�W�ԍ��̈ʒu�ƃT�C�Y
	std::map<int, XMFLOAT2> m_LevelPos;
	std::map<int, XMFLOAT2> m_LevelSize;
};