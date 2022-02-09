//=============================================================================
// StageSelectLogo.h
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
class CStageSelectLogo : public CBaseTexture
{
public:
	CStageSelectLogo();
	~CStageSelectLogo() = default;

	void Init()   override;
	void Uninit() override;
	void Update() override;
	void Draw()   override;
};