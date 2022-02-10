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
	constexpr XMFLOAT3 DefPos = XMFLOAT3(-200.0f, 720.0f, 50.0f); // ��ʍ����ɃZ�b�g
	constexpr XMINT2 DefCoord = XMINT2(0, 0);					  // �g��Ȃ�
	constexpr XMFLOAT3 DefScale = XMFLOAT3(1.0f, 1.0f, 1.0f);	  // �T�C�Y
	constexpr XMFLOAT3 DefRot = XMFLOAT3(0, -90.0f, 0);			  // �E�������悤��
	constexpr int CubeNum = 10;	 // �L���[�u�̕\�������鐔
}

//=============================================================================
// 
// �R���X�g���N�^
// 
//=============================================================================
TitleScene::TitleScene()
{
	// �V�[��No
	Singleton<SceneManager>::GetInstance().SetSceneNo(Scene_Title);

	m_nMenuIndex = eTitle_Start;
	m_bButton = false;
}

//=============================================================================
// 
// ����������
// 
//=============================================================================
void TitleScene::Init()
{
	// �J����
	Singleton<CCamera>::GetInstance().Init();

	// �v���C���[���f������
	ObjectManager::CreateObject<CTitlePlayerObj>(DefPos, DefCoord, DefScale, DefRot);

	// �L���[�u���f������
	for (int i = 0; i < CubeNum; i++)
	{
		XMFLOAT3 CubePos = XMFLOAT3(-500.0f + (i * 100.0f), 619.0f, 50.0f);
		ObjectManager::CreateObject<CTitleCubeObj>(CubePos, DefCoord, DefScale, DefRot);
	}
	// �^�C�g���e�N�X�`��������
	m_TitleTexture.Init();
	// �I�u�W�F�N�g������
	ObjectManager::InitAll();	 
}

//=============================================================================
// 
// �I������
// 
//=============================================================================
void TitleScene::Uninit()
{	
	// �I�u�W�F�N�g�I��
	ObjectManager::UninitAll();
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
void TitleScene::Update()
{
	// �^�C�g��BGM
	CSound::Play(TITLE);

	if (GetKeyTrigger(VK_W) || GetKeyTrigger(VK_UP))
	{
		// �J�[�\��SE
		CSound::Play(SE_CURSORMOVE);

		m_nMenuIndex--;
		if (m_nMenuIndex < eTitle_Start)
			m_nMenuIndex += eTitle_Max;
	}
	if (GetKeyTrigger(VK_S) || GetKeyTrigger(VK_DOWN))
	{
		// �J�[�\��SE
		CSound::Play(SE_CURSORMOVE);

		m_nMenuIndex++;
		if (m_nMenuIndex > eTitle_Exit)
			m_nMenuIndex -= eTitle_Max;
	}

	// �^�C�g���e�N�X�`���X�V
	m_TitleTexture.Update(m_nMenuIndex);

	// �I�u�W�F�N�g�X�V
	ObjectManager::UpdateAll();

	// �V�[���J��
	if (GetKeyTrigger(VK_RETURN) && !m_bButton)
	{
		// ����SE
		CSound::Play(SE_CHOISE);

		// �I�����ŃV�[���J��
		switch (m_nMenuIndex)
		{
		case (eTitle_Start):
			// �Q�[��
			m_bButton = true;
			SceneManager::GetInstance().SetNextScene(new StageSelectScene());
			break;
		case (eTitle_Edit):
			// �Q�[��
			m_bButton = true;
			SceneManager::GetInstance().SetNextScene(new EditScene());
			break;
		case (eTitle_Exit):
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
void TitleScene::Draw()
{
	// �^�C�g���e�N�X�`���`��
	m_TitleTexture.Draw();

	// �I�u�W�F�N�g�`��
	ObjectManager::DrawAll();
}