//=============================================================================
// GameOver.cpp
//=============================================================================
// Author  ���� ���V
//=============================================================================
#include "GameOver.h"
#include <Manager/GameManager.h>

//=============================================================================
// 
// �R���X�g���N�^
// 
//=============================================================================
CGameOver::CGameOver()
{
	// �C���X�^���X����
	m_GameOverBackGround = std::make_shared<CGameOverBackGround>();
	m_GameOverLogo = std::make_shared<CGameOverLogo>();

	// ���X�g�ǉ�
	m_pGameOverTextures.emplace_back(m_GameOverBackGround);
	m_pGameOverTextures.emplace_back(m_GameOverLogo);
}

//=============================================================================
// 
// ����������
// 
//=============================================================================
void CGameOver::Init()
{
	// ������
	for (auto& it : m_pGameOverTextures)
		it->Init();
}

//=============================================================================
// 
// �I������
// 
//=============================================================================
void CGameOver::Uninit()
{
	// �I��
	for (auto& it : m_pGameOverTextures)
		it->Uninit();
}

//=============================================================================
// 
// �X�V����
// 
//=============================================================================
void CGameOver::Update(GameState state)
{
	// �Q�[���I�[�o�[�ȊO�Ȃ�X�L�b�v
	if (state != GameState::eGameOver)	return;

	// �I��
	for (auto& it : m_pGameOverTextures)
		it->Update();
}

//=============================================================================
// 
// �`�揈��
// 
//=============================================================================
void CGameOver::Draw(GameState state)
{
	// �Q�[���I�[�o�[�ȊO�Ȃ�X�L�b�v
	if (state != GameState::eGameOver)	return;

	for (auto& it : m_pGameOverTextures)
		it->Draw();
}