//=============================================================================
// InstructionsScreen.h
//=============================================================================
// Author  ¼–ì «”V
//=============================================================================
#pragma once

#include <Manager/BaseTexture.h>
#include <Renderer/Polygon/CPolygon.h>

//=============================================================================
// 
// ƒNƒ‰ƒX’è‹`
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

	void PageMove(float& move);

private:
	std::vector<CPolygon> m_Polygons;
};

