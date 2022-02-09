//=============================================================================
// GameManager.h
//=============================================================================
// Author  ���� ���V
//=============================================================================
#pragma once

#include <Manager/StageManager.h>

//=============================================================================
// 
// �}�N����`
// 
//=============================================================================
// ���
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
// �N���X��`
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
	
	// setter
	static void SetState(GameState state) { m_GameState = state; }

	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

private:
	static GameState m_GameState;	// �Q�[�����̏��
	static int m_nStep;	// ����
	static int m_nStageMenuIndex; // �X�e�[�W�ԍ�
};