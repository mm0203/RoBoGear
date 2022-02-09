//=============================================================================
// StageSelectScene.cpp
//=============================================================================
// Author  松野 将之
//=============================================================================
#include "StageSelectScene.h"

// マネージャー
#include <Manager/GameManager.h>
#include <Manager/StageManager.h>

// シーン
#include <Scene/Title/TitleScene.h>
#include <Scene/Game/GameScene.h>

// システム
#include <System/Input/input.h>
#include <System/Debug/debugproc.h>
#include <System/Sound/Sound.h>
#include <tuple>

//=============================================================================
// 
// 無名名前空間
// 
//=============================================================================
namespace 
{
	constexpr int UpperLower = 5;	// 上下移動
	constexpr int TitleToLower = 10; // タイトルに
}

//=============================================================================
// 
// コンストラクタ
// 
//=============================================================================
StageSelectScene::StageSelectScene()
{
	Singleton<SceneManager>::GetInstance().SetSceneNo(Scene_StageSelect);
}

//=============================================================================
// 
// 初期化処理
// 
//=============================================================================
void StageSelectScene::Init()
{
	// 初期化
	m_StageSelectTexture.Init();
}

//=============================================================================
// 
// 終了処理
// 
//=============================================================================
void StageSelectScene::Uninit()
{
	// 終了
	m_StageSelectTexture.Uninit();
	// BGM終了
	CSound::Stop(STAGESELECT);
}

//=============================================================================
// 
// 更新処理
// 
//=============================================================================
void StageSelectScene::Update()
{
	CSound::Play(STAGESELECT);

	// ステージメニュー
	int& nMenuIndex = CGameManager::GetStageMenu();

	// ステージセレクト更新
	m_StageSelectTexture.Update(nMenuIndex);
	
	// 選択肢保存用
	static int nOldMenuIndex = 0;

	// 選択肢変更
	if (GetKeyTrigger(VK_W)) // カーソル上移動
	{
		// カーソルSE
		CSound::SetVolume(0.5f);
		CSound::Play(SE_CURSORMOVE);

		// 下段なら上段に
		if (nMenuIndex > eStage_5 && nMenuIndex <= eStage_10)
			nMenuIndex -= UpperLower;

		// タイトルバックなら下段に
		if (nMenuIndex == eTitleBack)	
			// 選択肢をさっきの下段の場所に
			nMenuIndex = nOldMenuIndex;
	}
	if (GetKeyTrigger(VK_S)) // カーソル下移動
	{
		// カーソルSE
		CSound::SetVolume(0.5f);
		CSound::Play(SE_CURSORMOVE);

		// 上段なら下段に
		if (nMenuIndex < eStage_6)
			nMenuIndex += UpperLower;

		// 下段ならタイトルバックに
		else if (nMenuIndex >= eStage_6 && nMenuIndex <= eStage_10)
		{
			// 下段にあった選択肢の場所を保存
			nOldMenuIndex = nMenuIndex;
			nMenuIndex += TitleToLower - nMenuIndex;
		}
		// タイトルバックなら下に移動できない
		else if (nMenuIndex == eTitleBack)
			nMenuIndex = eTitleBack;
	}
	if (GetKeyTrigger(VK_A)) // カーソル左移動
	{
		// カーソルSE
		CSound::SetVolume(0.5f);
		CSound::Play(SE_CURSORMOVE);

		// 上段か下段なら左右移動可
		if (nMenuIndex > eStage_1 && nMenuIndex <= eStage_10)
			nMenuIndex--;
	}
	if (GetKeyTrigger(VK_D)) // カーソル左移動
	{
		// カーソルSE
		CSound::SetVolume(0.5f);
		CSound::Play(SE_CURSORMOVE);

		// 上段か下段なら左右移動可
		if (nMenuIndex < eStage_10 && nMenuIndex >= eStage_1)
			nMenuIndex++;
	}

	// ゲーム画面以降
	if (GetKeyTrigger(VK_RETURN))
	{
		// 決定SE
		CSound::SetVolume(0.5f);
		CSound::Play(SE_CHOISE);

		// 選択肢がタイトルバックだったらタイトルへ
		if(nMenuIndex == eTitleBack)
			Singleton<SceneManager>::GetInstance().SetNextScene(new TitleScene());
		// タイトルバック以外ならゲームへ
		else
			Singleton<SceneManager>::GetInstance().SetNextScene(new GameScene());
	}

	PrintDebugProc("\CurrentStage:%d\n", nMenuIndex + 1);
}

//=============================================================================
// 
// 描画処理
// 
//=============================================================================
void StageSelectScene::Draw()
{
	// ステージテクスチャ描画
	m_StageSelectTexture.Draw();

}
