//=============================================================================
// CPauseMenuTexture.cpp
//=============================================================================
// Author  ���� ���V
//=============================================================================
#include "PauseMenuTexture.h"

//=============================================================================
// 
// �R���X�g���N�^
// 
//=============================================================================
CPauseMenuTexture::CPauseMenuTexture()
{
	// �C���X�^���X����
	m_PauseMenuBackGround = std::make_shared<CPauseMenuBackGround>();
	m_PauseMenuLogo = std::make_shared<CPauseMenuLogo>();
	m_PauseMenuChoices = std::make_shared<CPauseMenuChoices>();

	// TODO ���X�g�ɒǉ�
	m_pPauseTextures.emplace_back(m_PauseMenuBackGround);
	m_pPauseTextures.emplace_back(m_PauseMenuLogo);
	m_pPauseTextures.emplace_back(m_PauseMenuChoices);
}

//=============================================================================
// 
// ����������
// 
//=============================================================================
void CPauseMenuTexture::Init()
{
	for (auto& it : m_pPauseTextures)
		it->Init();
}

//=============================================================================
// 
// �I������
// 
//=============================================================================
void CPauseMenuTexture::Uninit()
{
	for (auto& it : m_pPauseTextures)
		it->Uninit();
}

//=============================================================================
// 
// �X�V����
// 
//=============================================================================
void CPauseMenuTexture::Update(int index)
{
	for (auto& it : m_pPauseTextures)
		it->Update();

	// �I�����F�ύX
	m_PauseMenuChoices->ColorChange(index);
}

//=============================================================================
// 
// �`�揈��
// 
//=============================================================================
void CPauseMenuTexture::Draw()
{
	for (auto& it : m_pPauseTextures)
		it->Draw();
}