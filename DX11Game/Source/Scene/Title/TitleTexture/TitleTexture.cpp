//=============================================================================
// CTitleTexture.cpp
//=============================================================================
// Author  ���� ���V
//=============================================================================
#include "TitleTexture.h"


//=============================================================================
// 
// �R���X�g���N�^
// 
//=============================================================================
CTitleTexture::CTitleTexture()
{
	// �C���X�^���X����
	m_TitleBackGround = std::make_shared<CTitleBackGround>();
	m_TitleFrame = std::make_shared<CTitleFrame>();
	m_TitleMenuChoices = std::make_shared<CTitleMenuChoices>();
	m_TitleLogo = std::make_shared<CTitleLogo>();

	// ���X�g�ǉ�
	m_pTitleTextures.emplace_back(m_TitleBackGround);
	m_pTitleTextures.emplace_back(m_TitleFrame);
	m_pTitleTextures.emplace_back(m_TitleMenuChoices);
	m_pTitleTextures.emplace_back(m_TitleLogo);
}

//=============================================================================
// 
// ����������
// 
//=============================================================================
void CTitleTexture::Init()
{
	// ������
	for (auto& it : m_pTitleTextures)
		it->Init();
}

//=============================================================================
// 
// �I������
// 
//=============================================================================
void CTitleTexture::Uninit()
{
	// �I��
	for (auto& it : m_pTitleTextures)
		it->Uninit();
}

//=============================================================================
// 
// �X�V����
// 
//=============================================================================
void CTitleTexture::Update(int index)
{
	// �X�V
	for (auto& it : m_pTitleTextures)
		it->Update();

	m_TitleMenuChoices->MenuChoices(index);
}

//=============================================================================
// 
// �`�揈��
// 
//=============================================================================
void CTitleTexture::Draw()
{
	// �`��
	for (auto& it : m_pTitleTextures)
		it->Draw();
}