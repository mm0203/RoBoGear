//=============================================================================
// PauseMenu.cpp
//=============================================================================
// Author  松野 将之
//=============================================================================
#include "PauseMenu.h"
#include <System/Input/input.h>
#include <Manager/GameManager.h>

// シーン
#include <Scene/Title/TitleScene.h>
#include <Scene/StageSelect/StageSelectScene.h>
#include <Scene/Game/GameScene.h>
#include <System/Sound/Sound.h>

//=============================================================================
// 
// コンストラクタ
// 
//=============================================================================
CPauseMenu::CPauseMenu()
{
	m_nMenuIndex = 0;
}

//=============================================================================
// 
// 初期化処理
// 
//=============================================================================
void CPauseMenu::Init()
{
	m_PuaseMenuTexture.Init();
}

//=============================================================================
// 
// 終了処理
// 
//=============================================================================
void CPauseMenu::Uninit()
{
	m_PuaseMenuTexture.Uninit();
}

//=============================================================================
// 
// 更新処理
// 
//=============================================================================
void CPauseMenu::Update(GameState state)
{
	// ポーズ以外ならスキップ
	if (state != GameState::ePause)	return;

	// ポーズテクスチャ更新
	m_PuaseMenuTexture.Update(m_nMenuIndex);

	// 選択肢変更
	if (GetKeyTrigger(VK_W) || GetKeyTrigger(VK_UP))
	{
		// 選択音
		CSound::Play(SE_CURSORMOVE);

		m_nMenuIndex--;
		if (m_nMenuIndex < ePause_Continue)
			m_nMenuIndex += ePauseMenuMax;
	}
	if (GetKeyTrigger(VK_S) || GetKeyTrigger(VK_DOWN))
	{
		// 選択音
		CSound::Play(SE_CURSORMOVE);

		m_nMenuIndex++;
		if (m_nMenuIndex > ePause_Title) 
			m_nMenuIndex -= ePauseMenuMax;
	}

	// 遷移
	if (GetKeyTrigger(VK_RETURN))
	{
		// 決定音
		CSound::Play(SE_CHOISE);

		// BGMの音量を戻す
		CSound::SetVolume(1.0f);

		// 選択肢でシーン遷移
		switch (m_nMenuIndex)
		{
		case (ePause_Continue):
			CGameManager::SetState(GameState::eMove);
			break;
		case (ePause_Retry):
			SceneManager::GetInstance().SetNextScene(new GameScene());
			break;
		case (ePause_StageSelect):
			SceneManager::GetInstance().SetNextScene(new StageSelectScene());
			break;
		case (ePause_Title):
			SceneManager::GetInstance().SetNextScene(new TitleScene());
			break;
		}
	}
}

//=============================================================================
// 
// 描画処理
// 
//=============================================================================
void CPauseMenu::Draw(GameState state)
{
	// ポーズ以外ならスキップ
	if (state != GameState::ePause)	return;

	m_PuaseMenuTexture.Draw();
}