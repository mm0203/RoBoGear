//=============================================================================
// CGameManager.cpp
//=============================================================================
// Author  ���� ���V
//=============================================================================
#include "GameManager.h"



// �V�X�e��
#include <System/Camera/Camera.h>
#include <System/Singleton/singleton.h>
#include <System/Input/input.h>
#include <System/Debug/debugproc.h>
#include <System/Message/Message.h>

// �V�[��
#include <Scene/Title/TitleScene.h>
#include <Scene/Game/GameScene.h>
#include <Scene/StageSelect/StageSelectScene.h>
#include <System/Sound/Sound.h>

//=============================================================================
// 
// �ÓI�����o
// 
//=============================================================================
GameState CGameManager::m_GameState;
int CGameManager::m_nStep;
int CGameManager::m_nStageMenuIndex;
bool CGameManager::m_bDebugMode;

//=============================================================================
// 
// ����������
// 
//=============================================================================
void CGameManager::Init()
{
	m_GameState = GameState::eStop;
	m_nStep = 99;
	m_bDebugMode = false;

	// �f�o�b�N���[�h�����\��
	MessageManager::Init();

	// �������F
	XMFLOAT3 color = XMFLOAT3(0.0f, 0.0f, 0.0f);

	MessageManager::CreateMessage("DEBUG MODE", XMFLOAT2(-600.0f, -300.0f),8);

	// �J��������\��
	MessageManager::CreateMessage("CAMERA", XMFLOAT2(300, 300.0f), 6);
	MessageManager::CreateMessage("MOVE  WASD", XMFLOAT2(360, 250.0f));
	MessageManager::CreateMessage("ANGLE IJKL", XMFLOAT2(360, 200.0f));
	MessageManager::CreateMessage("UP SPACE", XMFLOAT2(360, 150.0f));
	MessageManager::CreateMessage("DOWN CTRL", XMFLOAT2(360, 100.0f));

	// �V�F�[�_�؂�ւ��\��
	MessageManager::CreateMessage("SHADER", XMFLOAT2(300, 0.0f), 6);
	MessageManager::CreateMessage("TOON    Z", XMFLOAT2(360, -50.0f));
	MessageManager::CreateMessage("OUTLINE X", XMFLOAT2(360, -100.0f));
	MessageManager::CreateMessage("BUMP    C", XMFLOAT2(360, -150.0f));
	MessageManager::CreateMessage("ANBIENT V", XMFLOAT2(360, -200.0f));
}

//=============================================================================
// 
// �I������
// 
//=============================================================================
void CGameManager::Uninit()
{
	MessageManager::Uninit();
}

//=============================================================================
// 
// �X�V����
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
	case GameState::eStop:	// ��~

		nCount++;
		// �Q�[���J�n���J�������Y�[���A�E�g
		CCamera::GetInstance().ZoomOut();

		// 4�b��ɓ�����悤��
		if (nCount >= 60 * 4)
		{
			nCount = 0;
			m_GameState = GameState::eMove;
		}
		break;

	case GameState::eMove:	// ������
	
		// �|�[�Y
		if (GetKeyTrigger(VK_TAB) && m_GameState != GameState::eInstructions)
		{
			// �|�[�Y��
			CSound::Play(SE_PAUSE);
			// BGM��������
			CSound::SetVolume(0.3f);
			m_GameState = GameState::ePause;
		}
		// �������
		if (GetKeyTrigger(VK_R) && m_GameState != GameState::ePause)
		{
			// ���������
			CSound::Play(SE_PAUSE);
			// BGM��������
			CSound::SetVolume(0.3f);
			m_GameState = GameState::eInstructions;
		}
		break;

	case GameState::eClear: // �N���A
		nCount++;
		// �N���A5�b��ɃV�[���J��
		if (nCount >= 60 * 5)
		{
			nCount = 0;
			Singleton<SceneManager>::GetInstance().SetNextScene(new StageSelectScene());
		}	
		break;

	case GameState::eGameOver: // �Q�[���I�[�o�[
		nCount++;
		// �N���A3�b��ɃV�[���J��
		if (nCount >= 60 * 3)
		{
			nCount = 0;
			SceneManager::GetInstance().SetNextScene(new GameScene());
		}
		break;

	case GameState::ePause:	// �|�[�Y���
		if (GetKeyTrigger(VK_TAB))
		{
			// BGM�̉��ʂ�߂�
			CSound::SetVolume(1.0f);
			// ���鉹
			CSound::Play(SE_PAUSE_CLOSE);
			m_GameState = GameState::eMove;
		}
		break;
	case GameState::eInstructions:	// ����������
		if (GetKeyTrigger(VK_R) || GetKeyTrigger(VK_RETURN) || GetKeyTrigger(VK_SPACE))
		{
			// BGM�̉��ʂ�߂�
			CSound::SetVolume(1.0f);
			// ���鉹
			CSound::Play(SE_PAUSE_CLOSE);
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
// �`�揈��
// 
//=============================================================================
void CGameManager::Draw()
{
	// �f�o�b�O���[�h�`��
	if(m_bDebugMode)
	MessageManager::Draw();
}