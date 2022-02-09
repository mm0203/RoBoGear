//=============================================================================
// GameOver.cpp
//=============================================================================
// Author  松野 将之
//=============================================================================
#include "GameOver.h"
#include <Manager/GameManager.h>

//=============================================================================
// 
// コンストラクタ
// 
//=============================================================================
CGameOver::CGameOver()
{
	// インスタンス生成
	m_GameOverBackGround = std::make_shared<CGameOverBackGround>();
	m_GameOverLogo = std::make_shared<CGameOverLogo>();

	// リスト追加
	m_pGameOverTextures.emplace_back(m_GameOverBackGround);
	m_pGameOverTextures.emplace_back(m_GameOverLogo);
}

//=============================================================================
// 
// 初期化処理
// 
//=============================================================================
void CGameOver::Init()
{
	// 初期化
	for (auto& it : m_pGameOverTextures)
		it->Init();
}

//=============================================================================
// 
// 終了処理
// 
//=============================================================================
void CGameOver::Uninit()
{
	// 終了
	for (auto& it : m_pGameOverTextures)
		it->Uninit();
}

//=============================================================================
// 
// 更新処理
// 
//=============================================================================
void CGameOver::Update(GameState state)
{
	// ゲームオーバー以外ならスキップ
	if (state != GameState::eGameOver)	return;

	// 終了
	for (auto& it : m_pGameOverTextures)
		it->Update();
}

//=============================================================================
// 
// 描画処理
// 
//=============================================================================
void CGameOver::Draw(GameState state)
{
	// ゲームオーバー以外ならスキップ
	if (state != GameState::eGameOver)	return;

	for (auto& it : m_pGameOverTextures)
		it->Draw();
}