//=============================================================================
// GameManager.h
//=============================================================================
// Author  松野 将之
//=============================================================================
#pragma once

#include <Manager/StageManager.h>

//=============================================================================
// 
// マクロ定義
// 
//=============================================================================

// 秒数計算用
constexpr float Second = 60.0f;

// 状態
enum class GameState
{
	eStop = 0,
	eMove,
	eClear,
	eGameOver,
	ePause,
	eInstructions,
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
	
	// setter
	static void SetState(GameState state) { m_GameState = state; }

	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

private:
	static GameState m_GameState;	// ゲーム中の状態
	static int m_nStep;	// 歩数
	static int m_nStageMenuIndex; // ステージ番号
	static bool m_bDebugMode; // デバックモード
};