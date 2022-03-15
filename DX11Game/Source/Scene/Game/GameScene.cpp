//=============================================================================
// CGameScene.cpp
//=============================================================================
// Author  ���� ���V
//=============================================================================

#include "GameScene.h"

// �}�l�[�W���[
#include <Manager/SceneManager.h>
#include <Manager/StageManager.h>
#include <Manager/SpriteManager.h>
#include <Manager/ObjectManager.h>

// �V�[��
#include <Scene/StageSelect/StageSelectScene.h>
#include <Scene/Edit/Editor.h>

// �X�v���C�g
#include <Scene/Game/GameTexture/GameTexture.h>
#include <Scene/Game/GameOver/GameOver.h>
#include <Scene/Game/Instructions/Instructions.h>
#include <Scene/Pause/PauseMenu.h>

// �I�u�W�F�N�g
#include <Renderer/Effect/Effect.h>
#include <Object/StageGround.h>

// �V�X�e��
#include <System/Camera/Camera.h>
#include <System/Light/Light.h>
#include <System/Singleton/singleton.h>
#include <System/Input/input.h>
#include <System/Sound/Sound.h>

//=============================================================================
// 
// �R���X�g���N�^
// 
//=============================================================================
CGameScene::CGameScene() 
{
	CSingleton<CSceneManager>::GetInstance().SetSceneNo(eSceneGame);
	// �Q�[�����[�h
	m_State = GameState::eStop;
}

//=============================================================================
// 
// ����������
// 
//=============================================================================
void CGameScene::Init()
{
	// �Q�[������
	CGameManager::Init();
	// �J����
	CSingleton<CCamera>::GetInstance().Init();
	// �X�e�[�W����
	std::string StageFile = CStageManager::LoadStage();
	CStageManager::StageCreate(StageFile);
	// �n�ʐ���
	CObjectManager::CreateObject<CStageGround>();
	// �X�v���C�g�C���X�^���X����
	CreateSpriteInstance();
	// �S�X�v���C�g������
	CSpriteManager::InitAll();
	// �S�I�u�W�F�N�g������
	CObjectManager::InitAll();
}

//=============================================================================
// 
// �I������
// 
//=============================================================================
void CGameScene::Uninit()
{
	// �X�v���C�g�I��
	CSpriteManager::UninitAll();
	// �I�u�W�F�N�g�I��
	CObjectManager::UninitAll();
	// �Q�[������I��
	CGameManager::Uninit();
	// BGM��~
	CSound::Stop(GAME);
}

//=============================================================================
// 
// �X�V����
// 
//=============================================================================
void CGameScene::Update()
{
	// �Q�[������X�V
	CGameManager::Update();
	// ��Ԃ��擾
	m_State = CGameManager::GetState();

	if (m_State != GameState::eGameOver)
	{
		// �^�C�g��BGM
		CSound::Play(GAME);
	}

	// �|�[�Yor��������ŃQ�[���̍X�V��~
	if (m_State != GameState::ePause && m_State != GameState::eInstructions)
	{
		// �I�u�W�F�N�g�X�V
		CObjectManager::UpdateAll();
	}
	// �X�v���C�g�X�V
	CSpriteManager::UpdateAll(m_State);
}

//=============================================================================
// 
// �`�揈��
// 
//=============================================================================
void CGameScene::Draw()
{
	// �I�u�W�F�N�g�`��
	CObjectManager::DrawAll();
	// �X�v���C�g�`��
	CSpriteManager::DrawAll(m_State);
	// �Q�[������(�f�o�b�O�\�L)�`��
	CGameManager::Draw();
}

//=============================================================================
// 
// �X�v���C�g�C���X�^���X����
// 
//=============================================================================
void CGameScene::CreateSpriteInstance()
{
	// �G�t�F�N�g
	CSpriteManager::CreateSprite<CEffectManager>();
	// �Q�[��UI
	CSpriteManager::CreateSprite<CGameTexture>();
	// �Q�[���I�[�o�[
	CSpriteManager::CreateSprite<CGameOver>();
	// �|�[�Y
	CSpriteManager::CreateSprite<CPauseMenu>();
	// �������
	CSpriteManager::CreateSprite<CInstructions>();
}
