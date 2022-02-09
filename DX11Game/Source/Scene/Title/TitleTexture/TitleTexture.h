//=============================================================================
// CTitleTexture.h
//=============================================================================
// Author  èºñÏ è´îV
//=============================================================================
#pragma once

#include <Manager/BaseTexture.h>
#include "TitleMenuChoices.h"
#include "TitleBackGround.h"
#include "TitleLogo.h"
#include "TitleFrame.h"
#include <list>

//=============================================================================
// 
// ÉNÉâÉXíËã`
// 
//=============================================================================
class CTitleTexture
{
public:
	CTitleTexture();
	~CTitleTexture() = default;

	void Init();
	void Uninit();
	void Update(int index);
	void Draw();

private:
	std::shared_ptr<CTitleBackGround> m_TitleBackGround;
	std::shared_ptr<CTitleFrame> m_TitleFrame;
	std::shared_ptr<CTitleMenuChoices> m_TitleMenuChoices;
	std::shared_ptr<CTitleLogo> m_TitleLogo;

private:
	std::list<tex_shared> m_pTitleTextures;
};