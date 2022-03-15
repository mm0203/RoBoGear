//=============================================================================
// InstructionsScreen.h
//=============================================================================
// Author  松野 将之
//=============================================================================
#pragma once

#include <Manager/BaseTexture.h>
#include <Renderer/Polygon/CPolygon.h>

//=============================================================================
// 
// クラス定義
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

	// ページ切り替え時の移動量
	void PageMove(float& move);

private:
	std::vector<CPolygon> m_Polygons;
};

