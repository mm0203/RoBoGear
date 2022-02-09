//=============================================================================
// CPauseMenuLogo.h
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
class CPauseMenuLogo : public CBaseTexture
{
public:
	CPauseMenuLogo();
	~CPauseMenuLogo() = default;

	void Init()   override;
	void Uninit() override;
	void Update() override;
	void Draw()   override;
};