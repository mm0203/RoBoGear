//=============================================================================
// PauseMenuBackGround.h
//=============================================================================
// Author  ¼–ì «”V
//=============================================================================
#pragma once

#include <Manager/BaseTexture.h>

//=============================================================================
// 
// ƒNƒ‰ƒX’è‹`
// 
//=============================================================================
class CPauseMenuBackGround : public CBaseTexture
{
public:
	CPauseMenuBackGround() = default;
	~CPauseMenuBackGround() = default;

	void Init()   override;
	void Uninit() override;
	void Update() override;
	void Draw()   override;
};