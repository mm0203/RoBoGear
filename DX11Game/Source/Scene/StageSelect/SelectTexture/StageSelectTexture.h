//=============================================================================
// StageSelectTexture.h
//=============================================================================
// Author  èºñÏ è´îV
//=============================================================================
#pragma once

#include "StageSelectBackGround.h"
#include "StageSelectLogo.h"
#include "StageSelectCursor.h"
#include "StageSelectLevel.h"
#include <list>

//=============================================================================
// 
// ÉNÉâÉXíËã`
// 
//=============================================================================
class CStageSelectTexture
{
public:
	CStageSelectTexture();
	~CStageSelectTexture() = default;

	void Init();
	void Uninit();
	void Update(int index);
	void Draw();

private:
	std::shared_ptr<CStageSelectBackGround> m_StageSelectBackGround;
	std::shared_ptr<CStageSelectLogo> m_StageSelectLogo;
	std::shared_ptr<CStageSelectLevel> m_StageSelectLevel;
	std::shared_ptr<CStageSelectCursor> m_StageSelectCursor;
private:
	std::list<tex_shared> m_pStageSelectTextures;
};