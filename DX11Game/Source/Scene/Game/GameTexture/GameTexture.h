//=============================================================================
// CGameTexture.h
//=============================================================================
// Author  松野 将之
//=============================================================================
#pragma once

#include "GameBackGround.h"
#include "StartLogo.h"
#include "ClearLogo.h"
#include "GameStep.h"
#include <Manager/Sprite.h>
#include <list>

//=============================================================================
// 
// クラス定義
// 
//=============================================================================
class CGameTexture : public CSprite
{
public:
	CGameTexture();
	~CGameTexture() = default;

	void Init()   override;
	void Uninit() override;
	void Update(GameState state) override;
	void Draw(GameState state)   override;

private:
	// 秒数経過用
	int m_nCount;
	// 背景
	std::shared_ptr<CGameBackGround> m_GameBackGround;
	// 歩数
	std::shared_ptr<CGameStep> m_GameStep;
	// ステージ開始ロゴ
	std::shared_ptr<CStartLogo> m_Start;
	// クリアロゴ
	std::shared_ptr<CClearLogo> m_Clear;

private:
	std::list<tex_shared> m_pGameTextures;
};