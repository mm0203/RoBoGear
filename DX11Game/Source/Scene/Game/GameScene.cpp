//=============================================================================
// CGameScene.cpp
//=============================================================================
// Author  松野 将之
//=============================================================================

#include "GameScene.h"

// マネージャー
#include <Manager/SceneManager.h>
#include <Manager/StageManager.h>
#include <Manager/SpriteManager.h>
#include <Manager/ObjectManager.h>

// シーン
#include <Scene/StageSelect/StageSelectScene.h>
#include <Scene/Edit/Editor.h>

// スプライト
#include <Scene/Game/GameTexture/GameTexture.h>
#include <Scene/Game/GameOver/GameOver.h>
#include <Scene/Game/Instructions/Instructions.h>
#include <Scene/Pause/PauseMenu.h>

// オブジェクト
#include <Renderer/Effect/Effect.h>
#include <Object/StageGround.h>

// システム
#include <System/Camera/Camera.h>
#include <System/Light/Light.h>
#include <System/Singleton/singleton.h>
#include <System/Input/input.h>
#include <System/Sound/Sound.h>

//=============================================================================
// 
// コンストラクタ
// 
//=============================================================================
CGameScene::CGameScene() 
{
	CSingleton<CSceneManager>::GetInstance().SetSceneNo(eSceneGame);
	// ゲームモード
	m_State = GameState::eStop;
}

//=============================================================================
// 
// 初期化処理
// 
//=============================================================================
void CGameScene::Init()
{
	// ゲーム制御
	CGameManager::Init();
	// カメラ
	CSingleton<CCamera>::GetInstance().Init();
	// ステージ生成
	std::string StageFile = CStageManager::LoadStage();
	CStageManager::StageCreate(StageFile);
	// 地面生成
	CObjectManager::CreateObject<CStageGround>();
	// スプライトインスタンス生成
	CreateSpriteInstance();
	// 全スプライト初期化
	CSpriteManager::InitAll();
	// 全オブジェクト初期化
	CObjectManager::InitAll();
}

//=============================================================================
// 
// 終了処理
// 
//=============================================================================
void CGameScene::Uninit()
{
	// スプライト終了
	CSpriteManager::UninitAll();
	// オブジェクト終了
	CObjectManager::UninitAll();
	// ゲーム制御終了
	CGameManager::Uninit();
	// BGM停止
	CSound::Stop(GAME);
}

//=============================================================================
// 
// 更新処理
// 
//=============================================================================
void CGameScene::Update()
{
	// ゲーム制御更新
	CGameManager::Update();
	// 状態を取得
	m_State = CGameManager::GetState();

	if (m_State != GameState::eGameOver)
	{
		// タイトルBGM
		CSound::Play(GAME);
	}

	// ポーズor操作説明でゲームの更新停止
	if (m_State != GameState::ePause && m_State != GameState::eInstructions)
	{
		// オブジェクト更新
		CObjectManager::UpdateAll();
	}
	// スプライト更新
	CSpriteManager::UpdateAll(m_State);
}

//=============================================================================
// 
// 描画処理
// 
//=============================================================================
void CGameScene::Draw()
{
	// オブジェクト描画
	CObjectManager::DrawAll();
	// スプライト描画
	CSpriteManager::DrawAll(m_State);
	// ゲーム制御(デバッグ表記)描画
	CGameManager::Draw();
}

//=============================================================================
// 
// スプライトインスタンス生成
// 
//=============================================================================
void CGameScene::CreateSpriteInstance()
{
	// エフェクト
	CSpriteManager::CreateSprite<CEffectManager>();
	// ゲームUI
	CSpriteManager::CreateSprite<CGameTexture>();
	// ゲームオーバー
	CSpriteManager::CreateSprite<CGameOver>();
	// ポーズ
	CSpriteManager::CreateSprite<CPauseMenu>();
	// 操作説明
	CSpriteManager::CreateSprite<CInstructions>();
}
