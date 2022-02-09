//=============================================================================
// TitleFrame.h
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
class CTitleFrame : public CBaseTexture
{
public:
	CTitleFrame() = default;
	~CTitleFrame() = default;

	void Init()   override;
	void Uninit() override;
	void Update() override;
	void Draw()   override;
};