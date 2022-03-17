//=============================================================================
// GameTexture.cpp
//=============================================================================
// Author  ���� ���V
//=============================================================================
#include "GameTexture.h"
#include <Manager/GameManager.h>

//=============================================================================
// 
// �R���X�g���N�^
// 
//=============================================================================
CGameTexture::CGameTexture()
{
	m_nCount = 0;

	// �C���X�^���X����
	m_GameBackGround = std::make_shared<CGameBackGround>();
	m_GameStep = std::make_shared<CGameStep>();
	m_Start = std::make_shared<CStartLogo>();
	m_Clear = std::make_shared<CClearLogo>();

	// TODO ���X�g�ǉ�
	m_pGameTextures.emplace_back(m_GameBackGround);
	m_pGameTextures.emplace_back(m_GameStep);
	m_pGameTextures.emplace_back(m_Start);
	m_pGameTextures.emplace_back(m_Clear);
}

//=============================================================================
// 
// ����������
// 
//=============================================================================
void CGameTexture::Init()
{
	for (auto& it : m_pGameTextures)
		it->Init();
}

//=============================================================================
// 
// �I������
// 
//=============================================================================
void CGameTexture::Uninit()
{
	for (auto& it : m_pGameTextures)
		it->Uninit();
}

//=============================================================================
// 
// �X�V����
// 
//=============================================================================
void CGameTexture::Update(GameState state)
{
	// �|�[�Yor��������ŃQ�[��UI�X�V��~
	if (state == GameState::ePause || state == GameState::eInstructions) return;

	// �w�i�X�V
	m_GameBackGround->Update();
	// �����X�V
	m_GameStep->Update();

	switch (state)
	{
	case (GameState::eStop): // ��~
		// �X�^�[�g�\��
		m_Start->Update();
		break;

	case (GameState::eClear): // �N���A

		m_nCount++;

		// UI�Ƃ��S����\���ɂ���
		m_GameBackGround->FadeOut();
		m_GameStep->FadeOut();

		// �N���A3�b���
		if (m_nCount >= Second * 3)
		{
			// �N���A�\��
			m_Clear->Update();
		}
		break;

	case GameState::eGameOver: // �Q�[���I�[�o�[

		// UI�Ƃ��S����\���ɂ���
		m_GameBackGround->FadeOut();
		m_GameStep->FadeOut();

		break;
	}
}

//=============================================================================
// 
// �`�揈��
// 
//=============================================================================
void CGameTexture::Draw(GameState state)
{
	// �f�o�b�O���[�h�Ŕ�\��
	if (!CGameManager::GetDebug())
	{
		for (auto& it : m_pGameTextures)
			it->Draw();
	}
}