//=============================================================================
// CPauseMenuTexture.h
//=============================================================================
// Author  ¼–ì «”V
//=============================================================================
#pragma once

#include "PauseMenuBackGround.h"
#include "PauseMenuLogo.h"
#include "PauseMenuChoices.h"
#include <list>

//=============================================================================
// 
// ƒNƒ‰ƒX’è‹`
// 
//=============================================================================
class CPauseMenuTexture
{
public:
	CPauseMenuTexture();
	~CPauseMenuTexture() = default;

	void Init();
	void Uninit();
	void Update(int index);
	void Draw();

private:
	std::shared_ptr<CPauseMenuBackGround> m_PauseMenuBackGround;
	std::shared_ptr<CPauseMenuLogo> m_PauseMenuLogo;
	std::shared_ptr<CPauseMenuChoices> m_PauseMenuChoices;

private:
	std::list<tex_shared> m_pPauseTextures;
};