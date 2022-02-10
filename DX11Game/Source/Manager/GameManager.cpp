//=============================================================================
// CGameManager.cpp
//=============================================================================
// Author  松野 将之
//=============================================================================
#include "GameManager.h"



// システム
#include <System/Camera/Camera.h>
#include <System/Singleton/singleton.h>
#include <System/Input/input.h>
#include <System/Debug/debugproc.h>
#include <System/Message/Message.h>

// シーン
#include <Scene/Title/TitleScene.h>
#include <Scene/Game/GameScene.h>
#include <Scene/StageSelect/StageSelectScene.h>
#include <System/Sound/Sound.h>

//=============================================================================
// 
// 静的メンバ
// 
//=============================================================================
GameState CGameManager::m_GameState;
int CGameManager::m_nStep;
int CGameManager::m_nStageMenuIndex;
bool CGameManager::m_bDebugMode;

//=============================================================================
// 
// 初期化処理
// 
//=============================================================================
void CGameManager::Init()
{
	m_GameState = GameState::eStop;
	m_nStep = 99;
	m_bDebugMode = false;

	// デバックモード文字表示
	MessageManager::Init();

	// 文字黒色
	XMFLOAT3 color = XMFLOAT3(0.0f, 0.0f, 0.0f);

	MessageManager::CreateMessage("DEBUG MODE", XMFLOAT2(-600.0f, 300.0f),8);

	// カメラ操作表示
	MessageManager::CreateMessage("CAMERA", XMFLOAT2(300, 300.0f), 6);
	MessageManager::CreateMessage("MOVE  WASD", XMFLOAT2(360, 250.0f));
	MessageManager::CreateMessage("ANGLE IJKL", XMFLOAT2(360, 200.0f));
	MessageManager::CreateMessage("UP SPACE", XMFLOAT2(360, 150.0f));
	MessageManager::CreateMessage("DOWN CTRL", XMFLOAT2(360, 100.0f));

	// シェーダ切り替え表示
	MessageManager::CreateMessage("SHADER", XMFLOAT2(300, 0.0f), 6);
	MessageManager::CreateMessage("TOON    Z", XMFLOAT2(360, -50.0f));
	MessageManager::CreateMessage("OUTLINE X", XMFLOAT2(360, -100.0f));
	MessageManager::CreateMessage("BUMP    C", XMFLOAT2(360, -150.0f));
	MessageManager::CreateMessage("ANBIENT V", XMFLOAT2(360, -200.0f));
}

//=============================================================================
// 
// 終了処理
// 
//=============================================================================
void CGameManager::Uninit()
{
	MessageManager::Uninit();
}

//=============================================================================
// 
// 更新処理
// 
//=============================================================================
void CGameManager::Update()
{
	if (GetKeyTrigger(VK_F1))
		m_bDebugMode ^= 1;

	static int nCount = 0;
	static bool bPuase = false;
	static bool bInstructions = false;

	switch (m_GameState)
	{
	case GameState::eStop:	// 停止

		nCount++;
		// ゲーム開始時カメラをズームアウト
		CCamera::GetInstance().ZoomOut();

		// 4秒後に動けるように
		if (nCount >= 60 * 4)
		{
			nCount = 0;
			m_GameState = GameState::eMove;
		}
		break;

	case GameState::eMove:	// 動ける
	
		// ポーズ
		if (GetKeyTrigger(VK_TAB) && m_GameState != GameState::eInstructions)
		{
			// ポーズ音
			CSound::Play(SE_PAUSE);
			// BGMを小さく
			CSound::SetVolume(0.3f);
			m_GameState = GameState::ePause;
		}
		// 操作説明
		if (GetKeyTrigger(VK_R) && m_GameState != GameState::ePause)
		{
			// 操作説明音
			CSound::Play(SE_PAUSE);
			// BGMを小さく
			CSound::SetVolume(0.3f);
			m_GameState = GameState::eInstructions;
		}
		break;

	case GameState::eClear: // クリア
		nCount++;
		// クリア5秒後にシーン遷移
		if (nCount >= 60 * 5)
		{
			nCount = 0;
			Singleton<SceneManager>::GetInstance().SetNextScene(new StageSelectScene());
		}	
		break;

	case GameState::eGameOver: // ゲームオーバー
		nCount++;
		// クリア3秒後にシーン遷移
		if (nCount >= 60 * 3)
		{
			nCount = 0;
			SceneManager::GetInstance().SetNextScene(new GameScene());
		}
		break;

	case GameState::ePause:	// ポーズ画面
		if (GetKeyTrigger(VK_TAB))
		{
			// BGMの音量を戻す
			CSound::SetVolume(1.0f);
			// 閉じる音
			CSound::Play(SE_PAUSE_CLOSE);
			m_GameState = GameState::eMove;
		}
		break;
	case GameState::eInstructions:	// 操作説明画面
		if (GetKeyTrigger(VK_R) || GetKeyTrigger(VK_RETURN) || GetKeyTrigger(VK_SPACE))
		{
			// BGMの音量を戻す
			CSound::SetVolume(1.0f);
			// 閉じる音
			CSound::Play(SE_PAUSE_CLOSE);
			m_GameState = GameState::eMove;
		}
		break;
	default:
		break;
	}

	PrintDebugProc("\Step:%d\n", m_nStep);
}

//=============================================================================
// 
// 描画処理
// 
//=============================================================================
void CGameManager::Draw()
{
	if(m_bDebugMode)
	MessageManager::Draw();
}