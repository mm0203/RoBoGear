//=============================================================================
// StageSelectCursor.cpp
//=============================================================================
// Author  ���� ���V
//=============================================================================
#include "StageSelectCursor.h"
#include <Manager/StageManager.h>

//=============================================================================
// 
// �������O���
// 
//=============================================================================
namespace
{
	const auto StageSelectCursor = L"data/texture/StageSelect/cursor.png";
	const auto StageSelectCursorTitle = L"data/texture/StageSelect/selectCursorTitle.png";
}

//=============================================================================
// 
// �R���X�g���N�^
// 
//=============================================================================
CStageSelectCursor::CStageSelectCursor()
{
	m_TextureColor = std::make_shared<CTextureColorChangeComponent>();
}

//=============================================================================
// 
// ����������
// 
//=============================================================================
void CStageSelectCursor::Init()
{
	// �J�[�\��������
	m_Polygon->SetPosition(0, 100.0f);
	m_Polygon->SetSize(160.0f, 160.0f);
	m_Polygon->LoadTexture(StageSelectCursor);

	// ���x��������
	m_StageSelectLevel.Init();
}

//=============================================================================
// 
// �I������
// 
//=============================================================================
void CStageSelectCursor::Uninit()
{
	// ���x���I��
	m_StageSelectLevel.Uninit();
}

//=============================================================================
// 
// �X�V����
// 
//=============================================================================
void CStageSelectCursor::Update()
{
	// ���x���X�V
	m_StageSelectLevel.Update();

	// ���x���̐��l�ɍ��킹���ʒu�ƃT�C�Y���擾
	m_Polygon->SetPosition(m_StageSelectLevel.GetLevelPos());
	m_Polygon->SetSize(m_StageSelectLevel.GetLevelSize());

	// �J�[�\���F�ύX
	float color = m_TextureColor->ColorChange();
	m_Polygon->SetColor(0.0f, color, color);
}

//=============================================================================
// 
// �`�揈��
// 
//=============================================================================
void CStageSelectCursor::Draw()
{
	// ���x���`��
	m_StageSelectLevel.Draw();
	// �J�[�\���`��
	m_Polygon->Draw();
}

//=============================================================================
// 
// �e�N�X�`���ύX
// 
//=============================================================================
void CStageSelectCursor::TextureChage(int index)
{
	// �J�[�\���̃e�N�X�`���ύX
	if (index == eTitleBack)
		m_Polygon->LoadTexture(StageSelectCursorTitle);
	else
		m_Polygon->LoadTexture(StageSelectCursor);
}