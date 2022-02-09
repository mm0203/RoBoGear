//=============================================================================
// InstructionsBackGround.h
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
class CInstructionsBackGround : public CBaseTexture
{
public:
	CInstructionsBackGround() = default;
	~CInstructionsBackGround() = default;

	void Init()   override;
	void Uninit() override;
	void Update() override;
	void Draw()   override;
};

