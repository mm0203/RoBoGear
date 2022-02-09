//=============================================================================
// StageSelectLevel.h
//=============================================================================
// Author  松野 将之
//=============================================================================
#pragma once

#include <Manager/BaseTexture.h>
#include <Renderer/Polygon/CPolygon.h>
#include <map>

//=============================================================================
// 
// マクロ定義
// 
//=============================================================================


//=============================================================================
// 
// クラス定義
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

	XMFLOAT2 GetLevelPos();
	XMFLOAT2 GetLevelSize();

private:
	std::vector<CPolygon> m_Polygons;
	std::map<int, XMFLOAT2> m_LevelPos;
	std::map<int, XMFLOAT2> m_LevelSize;
};