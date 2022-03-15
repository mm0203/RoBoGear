//=============================================================================
// TitleScene.cpp
//=============================================================================
// Author  ���� ���V
//=============================================================================
#include "TitleScene.h"

// �V�X�e��
#include <System/Input/input.h>
#include <System/Debug/debugproc.h>
#include <System/Singleton/singleton.h>
#include <System/Sound/Sound.h>

// �}�l�[�W���[
#include <Manager/ObjectManager.h>

// �I�u�W�F�N�g
#include <Scene/Title/TitleObject/TitlePlayerObj.h>
#include <Scene/Title/TitleObject/TitleCubeObj.h>

// �V�[��
#include <Scene/Game/GameScene.h>
#include <Scene/StageSelect/StageSelectScene.h>
#include <Scene/Edit/EditScene.h>

//=============================================================================
// 
// �������O���
// 
//=============================================================================
namespace
{
	const XMFLOAT3 DefPos = XMFLOAT3(-200.0f, 720.0f, 50.0f); // ��ʍ����ɃZ�b�g
	const XMINT2 DefCoord = XMINT2(0, 0);					  // �g��Ȃ�
	const XMFLOAT3 DefScale = XMFLOAT3(1.0f, 1.0f, 1.0f);	  // �T�C�Y
	const XMFLOAT3 DefRot = XMFLOAT3(0, -90.0f, 0);			  // �E�������悤��
	const int CubeNum = 10;	 // �L���[�u�̕\�������鐔
}

//=============================================================================
// 
// �R���X�g���N�^
// 
//=============================================================================
CTitleScene::CTitleScene()
{
	// �V�[��No
	CSingleton<CSceneManager>::GetInstance().SetSceneNo(eSceneTitle);

	m_nMenuIndex = eTitle_Start;
	m_bButton = false;
}

//=============================================================================
// 
// ����������
// 
//=============================================================================
void CTitleScene::Init()
{
	// �J����
	CSingleton<CCamera>::GetInstance().Init();

	// �v���C���[���f������
	CObjectManager::CreateObject<CTitlePlayerObj>(DefPos, DefCoord, DefScale, DefRot);

	// �L���[�u���f������
	for (int i = 0; i < CubeNum; i++)
	{
		XMFLOAT3 CubePos = XMFLOAT3(-500.0f + (i * 100.0f), 619.0f, 50.0f);
		CObjectManager::CreateObject<CTitleCubeObj>(CubePos, DefCoord, DefScale, DefRot);
	}
	// �^�C�g���e�N�X�`��������
	m_TitleTexture.Init();
	// �I�u�W�F�N�g������
	CObjectManager::InitAll();	 
}

//=============================================================================
// 
// �I������
// 
//=============================================================================
void CTitleScene::Uninit()
{	
	// �I�u�W�F�N�g�I��
	CObjectManager::UninitAll();
	// �^�C�g���e�N�X�`���I��
	m_TitleTexture.Uninit();
	// BGM�I��
	CSound::Stop(TITLE);
}

//=============================================================================
// 
// �X�V����
// 
//=============================================================================
void CTitleScene::Update()
{
	// �^�C�g��BGM
	CSound::Play(TITLE);

	if (GetKeyTrigger(VK_W) || GetKeyTrigger(VK_UP))
	{
		// �J�[�\��SE
		CSound::Play(SE_CURSORMOVE);

		m_nMenuIndex--;

		// �P�ԏゾ������P�ԉ���
		if (m_nMenuIndex < eTitle_Start)
			m_nMenuIndex += eTitle_Max;
	}
	if (GetKeyTrigger(VK_S) || GetKeyTrigger(VK_DOWN))
	{
		// �J�[�\��SE
		CSound::Play(SE_CURSORMOVE);

		m_nMenuIndex++;

		// �P�ԉ���������P�ԏ��
		if (m_nMenuIndex > eTitle_Exit)
			m_nMenuIndex -= eTitle_Max;
	}

	// �^�C�g���e�N�X�`���X�V
	m_TitleTexture.Update(m_nMenuIndex);

	// �I�u�W�F�N�g�X�V
	CObjectManager::UpdateAll();

	// �V�[���J��
	if (GetKeyTrigger(VK_RETURN) && !m_bButton)
	{
		// ����SE
		CSound::Play(SE_CHOISE);

		// �I�����ŃV�[���J��
		switch (m_nMenuIndex)
		{
		case (eTitle_Start): // �Q�[����
			m_bButton = true;
			CSceneManager::GetInstance().SetNextScene(new CStageSelectScene());
			break;
		case (eTitle_Edit):	// �G�f�B�b�g��
			// �Q�[��
			m_bButton = true;
			CSceneManager::GetInstance().SetNextScene(new CEditScene());
			break;
		case (eTitle_Exit):	// �E�B���h�E�I��
			// �I��
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
// �`�揈��
// 
//=============================================================================
void CTitleScene::Draw()
{
	// �^�C�g���e�N�X�`���`��
	m_TitleTexture.Draw();

	// �I�u�W�F�N�g�`��
	CObjectManager::DrawAll();
}