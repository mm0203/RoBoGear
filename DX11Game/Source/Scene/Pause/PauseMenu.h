//=============================================================================
// PauseMenu.h
//=============================================================================
// Author  松野 将之
//=============================================================================
#pragma once

#include <Manager/Sprite.h>
#include <Scene/Pause/PauseTexture/PauseMenuTexture.h>

//=============================================================================
// 
// マクロ定義
// 
//=============================================================================
enum PauseMenu
{
	ePause_Continue,	// 続ける
	ePause_Retry,		// はじめから
	ePause_StageSelect,	// ステージセレクト
	ePause_Title,		// タイトル
	ePauseMenuMax
};
//=============================================================================
// 
// クラス定義
// 
//=============================================================================
class CPauseMenu : public CSprite
{
public:
	CPauseMenu();
	~CPauseMenu() = default;

	void Init()   override;
	void Uninit() override;
	void Update(GameState state) override;
	void Draw(GameState state)   override;

private:
	CPauseMenuTexture m_PuaseMenuTexture;
	// ポーズの選択肢
	int m_nMenuIndex;
};

