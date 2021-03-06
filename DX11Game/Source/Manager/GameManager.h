//=============================================================================
// GameManager.h
//=============================================================================
// Author  松野 将之
//=============================================================================
#pragma once

#include <Manager/StageManager.h>
#include <Scene/Game/TimeLeap/TimeLeap.h>

//=============================================================================
// 
// マクロ定義
// 
//=============================================================================

// 秒数計算用
const float Second = 60.0f;

// 状態
enum class GameState
{
	eStop = 0,		// 何もできない
	eMove,			// 動ける
	eClear,			// クリア
	eGameOver,		// ゲームオーバー
	ePause,			// ポーズ
	eInstructions,	// 操作説明
	eStateMax
};

//=============================================================================
// 
// クラス定義
// 
//=============================================================================
class CGameManager
{
public:
	CGameManager() = default;
	~CGameManager() = default;

	// getter
	static GameState GetState() { return m_GameState; }
	static int& GetStep() { return m_nStep; }
	static int& GetStageMenu() { return m_nStageMenuIndex; }
	static bool GetDebug() { return m_bDebugMode; }
	static CTimeLeap& GetTimeLeap(int objindex) { return m_TimeLeaps[objindex]; }
	// setter
	static void SetState(GameState state) { m_GameState = state; }

	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

private:
	// ゲーム中の状態
	static GameState m_GameState;
	// 歩数
	static int m_nStep;
	// ステージ番号
	static int m_nStageMenuIndex;
	// デバックモード
	static bool m_bDebugMode;
	// 巻き戻し用のスタックをオブジェクトの種類数用意
	static CTimeLeap m_TimeLeaps[eObject_Max - 1];
};