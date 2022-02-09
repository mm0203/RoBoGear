//=============================================================================
// StageSelectTexture.cpp
//=============================================================================
// Author  ���� ���V
//=============================================================================
#include "StageSelectTexture.h"

//=============================================================================
// 
// �R���X�g���N�^
// 
//=============================================================================
CStageSelectTexture::CStageSelectTexture()
{
	// �C���X�^���X����
	m_StageSelectBackGround = std::make_shared<CStageSelectBackGround>();
	m_StageSelectLogo = std::make_shared<CStageSelectLogo>();
	m_StageSelectLevel = std::make_shared<CStageSelectLevel>();
	m_StageSelectCursor = std::make_shared<CStageSelectCursor>();

	// TODO ���X�g�ǉ�
	m_pStageSelectTextures.emplace_back(m_StageSelectBackGround);
	m_pStageSelectTextures.emplace_back(m_StageSelectLogo);
	m_pStageSelectTextures.emplace_back(m_StageSelectLevel);
	m_pStageSelectTextures.emplace_back(m_StageSelectCursor);
}

//=============================================================================
// 
// ����������
// 
//=============================================================================
void CStageSelectTexture::Init()
{
	for (auto& it : m_pStageSelectTextures)
		it->Init();
}

//=============================================================================
// 
// �I������
// 
//=============================================================================
void CStageSelectTexture::Uninit()
{
	for (auto& it : m_pStageSelectTextures)
		it->Uninit();
}

//=============================================================================
// 
// �X�V����
// 
//=============================================================================
void CStageSelectTexture::Update(int index)
{
	for (auto& it : m_pStageSelectTextures)
		it->Update();

	// �e�N�X�`���ύX
	m_StageSelectCursor->TextureChage(index);

}

//=============================================================================
// 
// �`�揈��
// 
//=============================================================================
void CStageSelectTexture::Draw()
{
	for (auto& it : m_pStageSelectTextures)
		it->Draw();
}