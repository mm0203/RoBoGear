//=============================================================================
// StageSelectTexture.h
//=============================================================================
// Author  松野 将之
//=============================================================================
#pragma once

#include "StageSelectBackGround.h"
#include "StageSelectLogo.h"
#include "StageSelectCursor.h"
#include "StageSelectLevel.h"
#include <list>

//=============================================================================
// 
// クラス定義
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
	// 背景
	std::shared_ptr<CStageSelectBackGround> m_StageSelectBackGround;
	// ステージセレクトロゴ
	std::shared_ptr<CStageSelectLogo> m_StageSelectLogo;
	// 各ステージ番号
	std::shared_ptr<CStageSelectLevel> m_StageSelectLevel;
	// カーソル(枠線)
	std::shared_ptr<CStageSelectCursor> m_StageSelectCursor;
private:
	std::list<tex_shared> m_pStageSelectTextures;
};