//=============================================================================
// StageSelectScene.cpp
//=============================================================================
// Author  ���� ���V
//=============================================================================
#include "StageSelectScene.h"

// �}�l�[�W���[
#include <Manager/GameManager.h>
#include <Manager/StageManager.h>

// �V�[��
#include <Scene/Title/TitleScene.h>
#include <Scene/Game/GameScene.h>

// �V�X�e��
#include <System/Input/input.h>
#include <System/Debug/debugproc.h>
#include <System/Sound/Sound.h>
#include <tuple>

//=============================================================================
// 
// �������O���
// 
//=============================================================================
namespace 
{
	const int UpperLower = 5;	 // �㉺�ړ�
	const int TitleToLower = 10; // �^�C�g����
}

//=============================================================================
// 
// �R���X�g���N�^
// 
//=============================================================================
CStageSelectScene::CStageSelectScene()
{
	CSingleton<CSceneManager>::GetInstance().SetSceneNo(eSceneStageSelect);
}

//=============================================================================
// 
// ����������
// 
//=============================================================================
void CStageSelectScene::Init()
{
	// ������
	m_StageSelectTexture.Init();
}

//=============================================================================
// 
// �I������
// 
//=============================================================================
void CStageSelectScene::Uninit()
{
	// �I��
	m_StageSelectTexture.Uninit();
	// BGM�I��
	CSound::Stop(STAGESELECT);
}

//=============================================================================
// 
// �X�V����
// 
//=============================================================================
void CStageSelectScene::Update()
{
	CSound::Play(STAGESELECT);

	// �X�e�[�W���j���[
	int& nMenuIndex = CGameManager::GetStageMenu();

	// �X�e�[�W�Z���N�g�X�V
	m_StageSelectTexture.Update(nMenuIndex);
	
	// �I�����ۑ��p
	static int nOldMenuIndex = 0;

	// �I�����ύX
	if (GetKeyTrigger(VK_W)) // �J�[�\����ړ�
	{
		// �J�[�\��SE
		CSound::SetVolume(0.5f);
		CSound::Play(SE_CURSORMOVE);

		// ���i�Ȃ��i��
		if (nMenuIndex > eStage_5 && nMenuIndex <= eStage_10)
			nMenuIndex -= UpperLower;

		// �^�C�g���o�b�N�Ȃ牺�i��
		else if (nMenuIndex == eTitleBack)	
			// �I�������������̉��i�̏ꏊ��
			nMenuIndex = nOldMenuIndex;
	}
	if (GetKeyTrigger(VK_S)) // �J�[�\�����ړ�
	{
		// �J�[�\��SE
		CSound::SetVolume(0.5f);
		CSound::Play(SE_CURSORMOVE);

		// ��i�Ȃ牺�i��
		if (nMenuIndex < eStage_6)
			nMenuIndex += UpperLower;

		// ���i�Ȃ�^�C�g���o�b�N��
		else if (nMenuIndex >= eStage_6 && nMenuIndex <= eStage_10)
		{
			// ���i�ɂ������I�����̏ꏊ��ۑ�
			nOldMenuIndex = nMenuIndex;
			nMenuIndex += TitleToLower - nMenuIndex;
		}
		// �^�C�g���o�b�N�Ȃ牺�Ɉړ��ł��Ȃ�
		else if (nMenuIndex == eTitleBack)
			nMenuIndex = eTitleBack;
	}
	if (GetKeyTrigger(VK_A)) // �J�[�\�����ړ�
	{
		// �J�[�\��SE
		CSound::SetVolume(0.5f);
		CSound::Play(SE_CURSORMOVE);

		// ��i�����i�Ȃ獶�E�ړ���
		if (nMenuIndex > eStage_1 && nMenuIndex <= eStage_10)
			nMenuIndex--;
	}
	if (GetKeyTrigger(VK_D)) // �J�[�\�����ړ�
	{
		// �J�[�\��SE
		CSound::SetVolume(0.5f);
		CSound::Play(SE_CURSORMOVE);

		// ��i�����i�Ȃ獶�E�ړ���
		if (nMenuIndex < eStage_10 && nMenuIndex >= eStage_1)
			nMenuIndex++;
	}

	// �V�[���J��
	if (GetKeyTrigger(VK_RETURN))
	{
		// ����SE
		CSound::SetVolume(0.5f);
		CSound::Play(SE_CHOISE);

		// �I�������^�C�g���o�b�N��������^�C�g����
		if(nMenuIndex == eTitleBack)
			CSingleton<CSceneManager>::GetInstance().SetNextScene(new CTitleScene());
		// �^�C�g���o�b�N�ȊO�Ȃ�Q�[����
		else
			CSingleton<CSceneManager>::GetInstance().SetNextScene(new CGameScene());
	}

	PrintDebugProc("CurrentStage:%d\n", nMenuIndex + 1);
}

//=============================================================================
// 
// �`�揈��
// 
//=============================================================================
void CStageSelectScene::Draw()
{
	// �X�e�[�W�e�N�X�`���`��
	m_StageSelectTexture.Draw();

}
