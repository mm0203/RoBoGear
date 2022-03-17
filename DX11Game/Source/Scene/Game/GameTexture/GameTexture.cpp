//=============================================================================
// GameTexture.cpp
//=============================================================================
// Author  松野 将之
//=============================================================================
#include "GameTexture.h"
#include <Manager/GameManager.h>

//=============================================================================
// 
// コンストラクタ
// 
//=============================================================================
CGameTexture::CGameTexture()
{
	m_nCount = 0;

	// インスタンス生成
	m_GameBackGround = std::make_shared<CGameBackGround>();
	m_GameStep = std::make_shared<CGameStep>();
	m_Start = std::make_shared<CStartLogo>();
	m_Clear = std::make_shared<CClearLogo>();

	// TODO リスト追加
	m_pGameTextures.emplace_back(m_GameBackGround);
	m_pGameTextures.emplace_back(m_GameStep);
	m_pGameTextures.emplace_back(m_Start);
	m_pGameTextures.emplace_back(m_Clear);
}

//=============================================================================
// 
// 初期化処理
// 
//=============================================================================
void CGameTexture::Init()
{
	for (auto& it : m_pGameTextures)
		it->Init();
}

//=============================================================================
// 
// 終了処理
// 
//=============================================================================
void CGameTexture::Uninit()
{
	for (auto& it : m_pGameTextures)
		it->Uninit();
}

//=============================================================================
// 
// 更新処理
// 
//=============================================================================
void CGameTexture::Update(GameState state)
{
	// ポーズor操作説明でゲームUI更新停止
	if (state == GameState::ePause || state == GameState::eInstructions) return;

	// 背景更新
	m_GameBackGround->Update();
	// 歩数更新
	m_GameStep->Update();

	switch (state)
	{
	case (GameState::eStop): // 停止
		// スタート表示
		m_Start->Update();
		break;

	case (GameState::eClear): // クリア

		m_nCount++;

		// UIとか全部非表示にする
		m_GameBackGround->FadeOut();
		m_GameStep->FadeOut();

		// クリア3秒後に
		if (m_nCount >= Second * 3)
		{
			// クリア表示
			m_Clear->Update();
		}
		break;

	case GameState::eGameOver: // ゲームオーバー

		// UIとか全部非表示にする
		m_GameBackGround->FadeOut();
		m_GameStep->FadeOut();

		break;
	}
}

//=============================================================================
// 
// 描画処理
// 
//=============================================================================
void CGameTexture::Draw(GameState state)
{
	// デバッグモードで非表示
	if (!CGameManager::GetDebug())
	{
		for (auto& it : m_pGameTextures)
			it->Draw();
	}
}