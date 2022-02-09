//=============================================================================
// TitleBackGround.h
//=============================================================================
// Author  èºñÏ è´îV
//=============================================================================
#pragma once

#include <Manager/BaseTexture.h>

//=============================================================================
// 
// ÉNÉâÉXíËã`
// 
//=============================================================================
class CTitleBackGround : public CBaseTexture
{
public:
	CTitleBackGround() = default;
	~CTitleBackGround() = default;

	void Init()   override;
	void Uninit() override;
	void Update() override;
	void Draw()   override;

private:
	std::vector<CPolygon> m_Polygons;

private:
	enum eTitleBackGround
	{
		eFront_TitleBackGround = 0,
		eBack_TitleBackGround,
		eTitleBackGroundMax
	};
};