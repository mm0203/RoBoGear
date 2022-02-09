//=============================================================================
// CPauseMenuChoices.h
//=============================================================================
// Author  èºñÏ è´îV
//=============================================================================
#pragma once

#include <Manager/BaseTexture.h>
#include <Renderer/Polygon/CPolygon.h>

//=============================================================================
// 
// ÉNÉâÉXíËã`
// 
//=============================================================================
class CPauseMenuChoices : public CBaseTexture
{
public:
	CPauseMenuChoices();
	~CPauseMenuChoices() = default;

	void Init()   override;
	void Uninit() override;
	void Update() override;
	void Draw()   override;
	
	void ColorChange(int index);

private:
	std::vector<CPolygon> m_Polygons;
};