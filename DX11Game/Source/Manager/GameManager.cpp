//=============================================================================
// GameManager.cpp
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

// オブジェクト
#include <Object/Player.h>
#include <Object/Cube.h>
#include <Object/Key.h>
#include <Object/Gimic.h>

//=============================================================================
// 
// 静的メンバ
// 
//=============================================================================
GameState CGameManager::m_GameState;
int CGameManager::m_nStep;
int CGameManager::m_nStageMenuIndex;
bool CGameManager::m_bDebugMode;
CTimeLeap CGameManager::m_TimeLeaps[] = {};

//=============================================================================
// 
// 無名名前空間
// 
//=============================================================================
namespace
{
	// メッセージ表示サイズ
	const int MesseageSize = 6;
}
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
	CMessageManager::Init();

	// 文字黒色
	XMFLOAT3 color = XMFLOAT3(0.0f, 0.0f, 0.0f);

	CMessageManager::CreateMessage("DEBUG MODE", XMFLOAT2(-600.0f, -300.0f), MesseageSize);

	// カメラ操作表示
	CMessageManager::CreateMessage("CAMERA",     XMFLOAT2(300, 300.0f), MesseageSize);
	CMessageManager::CreateMessage("MOVE  WASD", XMFLOAT2(360, 250.0f));
	CMessageManager::CreateMessage("ANGLE IJKL", XMFLOAT2(360, 200.0f));
	CMessageManager::CreateMessage("UP SPACE",   XMFLOAT2(360, 150.0f));
	CMessageManager::CreateMessage("DOWN CTRL",  XMFLOAT2(360, 100.0f));

	// シェーダ切り替え表示
	CMessageManager::CreateMessage("SHADER",    XMFLOAT2(300, 0.0f), MesseageSize);
	CMessageManager::CreateMessage("TOON    Z", XMFLOAT2(360, -50.0f));
	CMessageManager::CreateMessage("OUTLINE X", XMFLOAT2(360, -100.0f));
	CMessageManager::CreateMessage("BUMP    C", XMFLOAT2(360, -150.0f));
	CMessageManager::CreateMessage("ANBIENT V", XMFLOAT2(360, -200.0f));
}

//=============================================================================
// 
// 終了処理
// 
//=============================================================================
void CGameManager::Uninit()
{
	// メッセージ終了
	CMessageManager::Uninit();

	// 巻き戻し用スタック解放
	for (int i = 0; i < eObject_Max - 1; i++)
	{
		m_TimeLeaps[i].ReleaseStack();
	}
}

//=============================================================================
// 
// 更新処理
// 
//=============================================================================
void CGameManager::Update()
{
	// デバッグ切り替え
	if (GetKeyTrigger(VK_F1))
		m_bDebugMode ^= 1;

	// カウント用
	static int nCount = 0;

	switch (m_GameState)
	{
	case GameState::eStop:	// 停止

		nCount++;
		// ゲーム開始時カメラをズームアウト
		CSingleton<CCamera>::GetInstance().ZoomOut();

		// 4秒後に動けるように
		if (nCount >= Second * 4)
		{
			nCount = 0;
			m_GameState = GameState::eMove;
		}
		break;

	case GameState::eMove:	// 動ける
	
		// 巻き戻し
		if (m_TimeLeaps[eObject_Player].GetCoordStack().size() > 1 && GetKeyTrigger(VK_Q))
		{
			// 巻き戻し音
			CSound::Play(SE_TIMELEAP);

			// プレイヤー
			m_TimeLeaps[eObject_Player].RewindObject(TagPlayer);
			m_TimeLeaps[eObject_Player].RewindRoationObject(TagPlayer);
			// キューブ
			m_TimeLeaps[eObject_Cube].RewindObject(TagCube);
			// 鍵
			m_TimeLeaps[eObject_Key].RevivalObject(TagKey);
			// ギミック
			m_TimeLeaps[eObject_Gimic].RevivalObject(TagGimic);
		}

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
		if (nCount >= Second * 5)
		{
			nCount = 0;
			CSingleton<CSceneManager>::GetInstance().SetNextScene(new CStageSelectScene());
		}	
		break;

	case GameState::eGameOver: // ゲームオーバー
		nCount++;
		// クリア3秒後にシーン遷移
		if (nCount >= Second * 3)
		{
			nCount = 0;
			CSceneManager::GetInstance().SetNextScene(new CGameScene());
		}
		break;

	case GameState::ePause:	// ポーズ画面

		// ポーズ閉じる
		if (GetKeyTrigger(VK_TAB))
		{
			// BGMの音量を戻す
			CSound::SetVolume(1.0f);
			// 閉じる音
			CSound::Play(SE_PAUSE_CLOSE);
			// 動ける状態に
			m_GameState = GameState::eMove;
		}
		break;
	case GameState::eInstructions:	// 操作説明画面

		// 操作説明閉じる
		if (GetKeyTrigger(VK_R) || GetKeyTrigger(VK_RETURN) || GetKeyTrigger(VK_SPACE))
		{
			// BGMの音量を戻す
			CSound::SetVolume(1.0f);
			// 閉じる音
			CSound::Play(SE_PAUSE_CLOSE);
			// 動ける状態に
			m_GameState = GameState::eMove;
		}
		break;
	default:
		break;
	}

	PrintDebugProc("Step:%d\n", m_nStep);
}

//=============================================================================
// 
// 描画処理
// 
//=============================================================================
void CGameManager::Draw()
{
	// デバッグモード描画
	if(m_bDebugMode)
	CMessageManager::Draw();
}