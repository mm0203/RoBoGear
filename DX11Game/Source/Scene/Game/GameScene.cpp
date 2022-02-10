//=============================================================================
// GameScene.cpp
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
GameScene::GameScene() 
{
	Singleton<SceneManager>::GetInstance().SetSceneNo(Scene_Game);
	// �Q�[�����[�h
	m_State = GameState::eStop;
}

//=============================================================================
// 
// ����������
// 
//=============================================================================
void GameScene::Init()
{
	// �Q�[������
	CGameManager::Init();
	// �J����
	Singleton<CCamera>::GetInstance().Init();
	// �X�e�[�W����
	std::string StageFile = StageManager::LoadStage();
	StageManager::StageCreate(StageFile);
	// �n�ʐ���
	ObjectManager::CreateObject<CStageGround>();
	// �X�v���C�g�C���X�^���X����
	CreateSpriteInstance();
	// �S�X�v���C�g������
	SpriteManager::InitAll();
	// �S�I�u�W�F�N�g������
	ObjectManager::InitAll();
}

//=============================================================================
// 
// �I������
// 
//=============================================================================
void GameScene::Uninit()
{
	// �X�v���C�g�I��
	SpriteManager::UninitAll();
	// �I�u�W�F�N�g�I��
	ObjectManager::UninitAll();
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
void GameScene::Update()
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
		ObjectManager::UpdateAll();
	}
	// �X�v���C�g�X�V
	SpriteManager::UpdateAll(m_State);
}

//=============================================================================
// 
// �`�揈��
// 
//=============================================================================
void GameScene::Draw()
{
	// �I�u�W�F�N�g�`��
	ObjectManager::DrawAll();
	// �X�v���C�g�`��
	SpriteManager::DrawAll(m_State);
	// �Q�[������(�f�o�b�O�\�L)�`��
	CGameManager::Draw();
}

//=============================================================================
// 
// �X�v���C�g�C���X�^���X����
// 
//=============================================================================
void GameScene::CreateSpriteInstance()
{
	// �G�t�F�N�g
	SpriteManager::CreateSprite<EffectManager>();
	// �Q�[��UI
	SpriteManager::CreateSprite<CGameTexture>();
	// �Q�[���I�[�o�[
	SpriteManager::CreateSprite<CGameOver>();
	// �|�[�Y
	SpriteManager::CreateSprite<CPauseMenu>();
	// �������
	SpriteManager::CreateSprite<CInstructions>();
}
