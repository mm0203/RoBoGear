//=============================================================================
// TitleScene.cpp
//=============================================================================
// Author  松野 将之
//=============================================================================
#include "TitleScene.h"

// システム
#include <System/Input/input.h>
#include <System/Debug/debugproc.h>
#include <System/Singleton/singleton.h>
#include <System/Sound/Sound.h>

// マネージャー
#include <Manager/ObjectManager.h>

// オブジェクト
#include <Scene/Title/TitleObject/TitlePlayerObj.h>
#include <Scene/Title/TitleObject/TitleCubeObj.h>

// シーン
#include <Scene/Game/GameScene.h>
#include <Scene/StageSelect/StageSelectScene.h>
#include <Scene/Edit/EditScene.h>

//=============================================================================
// 
// 無名名前空間
// 
//=============================================================================
namespace
{
	constexpr XMFLOAT3 DefPos = XMFLOAT3(-200.0f, 720.0f, 50.0f); // 画面左下にセット
	constexpr XMINT2 DefCoord = XMINT2(0, 0);					  // 使わない
	constexpr XMFLOAT3 DefScale = XMFLOAT3(1.0f, 1.0f, 1.0f);	  // サイズ
	constexpr XMFLOAT3 DefRot = XMFLOAT3(0, -90.0f, 0);			  // 右を向くように
	constexpr int CubeNum = 10;	 // キューブの表示させる数
}

//=============================================================================
// 
// コンストラクタ
// 
//=============================================================================
TitleScene::TitleScene()
{
	// シーンNo
	Singleton<SceneManager>::GetInstance().SetSceneNo(Scene_Title);

	m_nMenuIndex = eTitle_Start;
	m_bButton = false;
}

//=============================================================================
// 
// 初期化処理
// 
//=============================================================================
void TitleScene::Init()
{
	// カメラ
	Singleton<CCamera>::GetInstance().Init();

	// プレイヤーモデル生成
	ObjectManager::CreateObject<CTitlePlayerObj>(DefPos, DefCoord, DefScale, DefRot);

	// キューブモデル生成
	for (int i = 0; i < CubeNum; i++)
	{
		XMFLOAT3 CubePos = XMFLOAT3(-500.0f + (i * 100.0f), 619.0f, 50.0f);
		ObjectManager::CreateObject<CTitleCubeObj>(CubePos, DefCoord, DefScale, DefRot);
	}
	// タイトルテクスチャ初期化
	m_TitleTexture.Init();
	// オブジェクト初期化
	ObjectManager::InitAll();	 
}

//=============================================================================
// 
// 終了処理
// 
//=============================================================================
void TitleScene::Uninit()
{	
	// オブジェクト終了
	ObjectManager::UninitAll();
	// タイトルテクスチャ終了
	m_TitleTexture.Uninit();
	// BGM終了
	CSound::Stop(TITLE);
}

//=============================================================================
// 
// 更新処理
// 
//=============================================================================
void TitleScene::Update()
{
	// タイトルBGM
	CSound::Play(TITLE);

	if (GetKeyTrigger(VK_W) || GetKeyTrigger(VK_UP))
	{
		// カーソルSE
		CSound::Play(SE_CURSORMOVE);

		m_nMenuIndex--;
		if (m_nMenuIndex < eTitle_Start)
			m_nMenuIndex += eTitle_Max;
	}
	if (GetKeyTrigger(VK_S) || GetKeyTrigger(VK_DOWN))
	{
		// カーソルSE
		CSound::Play(SE_CURSORMOVE);

		m_nMenuIndex++;
		if (m_nMenuIndex > eTitle_Exit)
			m_nMenuIndex -= eTitle_Max;
	}

	// タイトルテクスチャ更新
	m_TitleTexture.Update(m_nMenuIndex);

	// オブジェクト更新
	ObjectManager::UpdateAll();

	// シーン遷移
	if (GetKeyTrigger(VK_RETURN) && !m_bButton)
	{
		// 決定SE
		CSound::Play(SE_CHOISE);

		// 選択肢でシーン遷移
		switch (m_nMenuIndex)
		{
		case (eTitle_Start):
			// ゲーム
			m_bButton = true;
			SceneManager::GetInstance().SetNextScene(new StageSelectScene());
			break;
		case (eTitle_Edit):
			// ゲーム
			m_bButton = true;
			SceneManager::GetInstance().SetNextScene(new EditScene());
			break;
		case (eTitle_Exit):
			// 終了
			m_bButton = true;
			HWND hWnd = GetMainWnd();
			PostMessage(hWnd, WM_CLOSE, 0, 0);
			break;
		}	
	}

	PrintDebugProc("MenuIndex:%d\n", m_nMenuIndex);
}

//=============================================================================
// 
// 描画処理
// 
//=============================================================================
void TitleScene::Draw()
{
	// タイトルテクスチャ描画
	m_TitleTexture.Draw();

	// オブジェクト描画
	ObjectManager::DrawAll();
}