//=============================================================================
// GameManager.cpp
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

// �I�u�W�F�N�g
#include <Object/Player.h>
#include <Object/Cube.h>
#include <Object/Key.h>
#include <Object/Gimic.h>

//=============================================================================
// 
// �ÓI�����o
// 
//=============================================================================
GameState CGameManager::m_GameState;
int CGameManager::m_nStep;
int CGameManager::m_nStageMenuIndex;
bool CGameManager::m_bDebugMode;
CTimeLeap CGameManager::m_TimeLeaps[] = {};

//=============================================================================
// 
// �������O���
// 
//=============================================================================
namespace
{
	// ���b�Z�[�W�\���T�C�Y
	const int MesseageSize = 6;
}
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
	CMessageManager::Init();

	// �������F
	XMFLOAT3 color = XMFLOAT3(0.0f, 0.0f, 0.0f);

	CMessageManager::CreateMessage("DEBUG MODE", XMFLOAT2(-600.0f, -300.0f), MesseageSize);

	// �J��������\��
	CMessageManager::CreateMessage("CAMERA",     XMFLOAT2(300, 300.0f), MesseageSize);
	CMessageManager::CreateMessage("MOVE  WASD", XMFLOAT2(360, 250.0f));
	CMessageManager::CreateMessage("ANGLE IJKL", XMFLOAT2(360, 200.0f));
	CMessageManager::CreateMessage("UP SPACE",   XMFLOAT2(360, 150.0f));
	CMessageManager::CreateMessage("DOWN CTRL",  XMFLOAT2(360, 100.0f));

	// �V�F�[�_�؂�ւ��\��
	CMessageManager::CreateMessage("SHADER",    XMFLOAT2(300, 0.0f), MesseageSize);
	CMessageManager::CreateMessage("TOON    Z", XMFLOAT2(360, -50.0f));
	CMessageManager::CreateMessage("OUTLINE X", XMFLOAT2(360, -100.0f));
	CMessageManager::CreateMessage("BUMP    C", XMFLOAT2(360, -150.0f));
	CMessageManager::CreateMessage("ANBIENT V", XMFLOAT2(360, -200.0f));
}

//=============================================================================
// 
// �I������
// 
//=============================================================================
void CGameManager::Uninit()
{
	// ���b�Z�[�W�I��
	CMessageManager::Uninit();

	// �����߂��p�X�^�b�N���
	for (int i = 0; i < eObject_Max - 1; i++)
	{
		m_TimeLeaps[i].ReleaseStack();
	}
}

//=============================================================================
// 
// �X�V����
// 
//=============================================================================
void CGameManager::Update()
{
	// �f�o�b�O�؂�ւ�
	if (GetKeyTrigger(VK_F1))
		m_bDebugMode ^= 1;

	// �J�E���g�p
	static int nCount = 0;

	switch (m_GameState)
	{
	case GameState::eStop:	// ��~

		nCount++;
		// �Q�[���J�n���J�������Y�[���A�E�g
		CSingleton<CCamera>::GetInstance().ZoomOut();

		// 4�b��ɓ�����悤��
		if (nCount >= Second * 4)
		{
			nCount = 0;
			m_GameState = GameState::eMove;
		}
		break;

	case GameState::eMove:	// ������
	
		// �����߂�
		if (m_TimeLeaps[eObject_Player].GetCoordStack().size() > 1 && GetKeyTrigger(VK_Q))
		{
			// �����߂���
			CSound::Play(SE_TIMELEAP);

			// �v���C���[
			m_TimeLeaps[eObject_Player].RewindObject(TagPlayer);
			m_TimeLeaps[eObject_Player].RewindRoationObject(TagPlayer);
			// �L���[�u
			m_TimeLeaps[eObject_Cube].RewindObject(TagCube);
			// ��
			m_TimeLeaps[eObject_Key].RevivalObject(TagKey);
			// �M�~�b�N
			m_TimeLeaps[eObject_Gimic].RevivalObject(TagGimic);
		}

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
		if (nCount >= Second * 5)
		{
			nCount = 0;
			CSingleton<CSceneManager>::GetInstance().SetNextScene(new CStageSelectScene());
		}	
		break;

	case GameState::eGameOver: // �Q�[���I�[�o�[
		nCount++;
		// �N���A3�b��ɃV�[���J��
		if (nCount >= Second * 3)
		{
			nCount = 0;
			CSceneManager::GetInstance().SetNextScene(new CGameScene());
		}
		break;

	case GameState::ePause:	// �|�[�Y���

		// �|�[�Y����
		if (GetKeyTrigger(VK_TAB))
		{
			// BGM�̉��ʂ�߂�
			CSound::SetVolume(1.0f);
			// ���鉹
			CSound::Play(SE_PAUSE_CLOSE);
			// �������Ԃ�
			m_GameState = GameState::eMove;
		}
		break;
	case GameState::eInstructions:	// ����������

		// �����������
		if (GetKeyTrigger(VK_R) || GetKeyTrigger(VK_RETURN) || GetKeyTrigger(VK_SPACE))
		{
			// BGM�̉��ʂ�߂�
			CSound::SetVolume(1.0f);
			// ���鉹
			CSound::Play(SE_PAUSE_CLOSE);
			// �������Ԃ�
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
	CMessageManager::Draw();
}