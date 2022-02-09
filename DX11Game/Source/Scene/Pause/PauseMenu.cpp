//=============================================================================
// PauseMenu.cpp
//=============================================================================
// Author  ���� ���V
//=============================================================================
#include "PauseMenu.h"
#include <System/Input/input.h>
#include <Manager/GameManager.h>

// �V�[��
#include <Scene/Title/TitleScene.h>
#include <Scene/StageSelect/StageSelectScene.h>
#include <Scene/Game/GameScene.h>
#include <System/Sound/Sound.h>

//=============================================================================
// 
// �R���X�g���N�^
// 
//=============================================================================
CPauseMenu::CPauseMenu()
{
	m_nMenuIndex = 0;
}

//=============================================================================
// 
// ����������
// 
//=============================================================================
void CPauseMenu::Init()
{
	m_PuaseMenuTexture.Init();
}

//=============================================================================
// 
// �I������
// 
//=============================================================================
void CPauseMenu::Uninit()
{
	m_PuaseMenuTexture.Uninit();
}

//=============================================================================
// 
// �X�V����
// 
//=============================================================================
void CPauseMenu::Update(GameState state)
{
	// �|�[�Y�ȊO�Ȃ�X�L�b�v
	if (state != GameState::ePause)	return;

	// �|�[�Y�e�N�X�`���X�V
	m_PuaseMenuTexture.Update(m_nMenuIndex);

	// �I�����ύX
	if (GetKeyTrigger(VK_W))
	{
		// �I����
		CSound::Play(SE_CURSORMOVE);

		m_nMenuIndex--;
		if (m_nMenuIndex < ePause_Continue)
			m_nMenuIndex += ePauseMenuMax;
	}
	if (GetKeyTrigger(VK_S))
	{
		// �I����
		CSound::Play(SE_CURSORMOVE);

		m_nMenuIndex++;
		if (m_nMenuIndex > ePause_Title) 
			m_nMenuIndex -= ePauseMenuMax;
	}

	// �J��
	if (GetKeyTrigger(VK_RETURN))
	{
		// ���艹
		CSound::Play(SE_CHOISE);

		// BGM�̉��ʂ�߂�
		CSound::SetVolume(1.0f);

		// �I�����ŃV�[���J��
		switch (m_nMenuIndex)
		{
		case (ePause_Continue):
			CGameManager::SetState(GameState::eMove);
			break;
		case (ePause_Retry):
			SceneManager::GetInstance().SetNextScene(new GameScene());
			break;
		case (ePause_StageSelect):
			SceneManager::GetInstance().SetNextScene(new StageSelectScene());
			break;
		case (ePause_Title):
			SceneManager::GetInstance().SetNextScene(new TitleScene());
			break;
		}
	}
}

//=============================================================================
// 
// �`�揈��
// 
//=============================================================================
void CPauseMenu::Draw(GameState state)
{
	// �|�[�Y�ȊO�Ȃ�X�L�b�v
	if (state != GameState::ePause)	return;

	m_PuaseMenuTexture.Draw();
}