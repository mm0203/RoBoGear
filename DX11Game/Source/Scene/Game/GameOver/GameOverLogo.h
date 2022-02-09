//=============================================================================
// GameOverLogo.h
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
class CGameOverLogo : public CBaseTexture
{
public:
	CGameOverLogo();
	~CGameOverLogo() = default;

	void Init()   override;
	void Uninit() override;
	void Update() override;
	void Draw()   override;
};