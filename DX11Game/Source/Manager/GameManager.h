//=============================================================================
// GameManager.h
//=============================================================================
// Author  ���� ���V
//=============================================================================
#pragma once

#include <Manager/StageManager.h>
#include <Scene/Game/TimeLeap/TimeLeap.h>

//=============================================================================
// 
// �}�N����`
// 
//=============================================================================

// �b���v�Z�p
const float Second = 60.0f;

// ���
enum class GameState
{
	eStop = 0,		// �����ł��Ȃ�
	eMove,			// ������
	eClear,			// �N���A
	eGameOver,		// �Q�[���I�[�o�[
	ePause,			// �|�[�Y
	eInstructions,	// �������
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
	static bool GetDebug() { return m_bDebugMode; }
	static CTimeLeap& GetTimeLeap(int objindex) { return m_TimeLeaps[objindex]; }
	// setter
	static void SetState(GameState state) { m_GameState = state; }

	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

private:
	// �Q�[�����̏��
	static GameState m_GameState;
	// ����
	static int m_nStep;
	// �X�e�[�W�ԍ�
	static int m_nStageMenuIndex;
	// �f�o�b�N���[�h
	static bool m_bDebugMode;
	// �����߂��p�̃X�^�b�N���I�u�W�F�N�g�̎�ސ��p��
	static CTimeLeap m_TimeLeaps[eObject_Max - 1];
};