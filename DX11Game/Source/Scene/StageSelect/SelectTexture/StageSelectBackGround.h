//=============================================================================
// StageBackGround.h
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
class CStageSelectBackGround : public CBaseTexture
{
public:
	CStageSelectBackGround() = default;
	~CStageSelectBackGround() = default;

	void Init()   override;
	void Uninit() override;
	void Update() override;
	void Draw()   override;
};