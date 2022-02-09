//=============================================================================
// InstructionsCursor.cpp
//=============================================================================
// Author  ���� ���V
//=============================================================================

#include "InstructionsCursor.h"
#include "Instructions.h"

//=============================================================================
// 
// �������O���
// 
//=============================================================================
namespace
{
	const auto InstructionsCursorRight = L"data/texture/Instructions/CursorA.png";
	const auto InstructionsCursorLeft  = L"data/texture/Instructions/CursorD.png";
}

//=============================================================================
// 
// ����������
// 
//=============================================================================
void CInstructionsCursor::Init()
{
	m_Polygons.resize(eCursorMax);
	m_TextureMoves.resize(eCursorMax);

	// �J�[�\��
	m_Polygons[eRight].SetSize(100.0f, 100.0f);
	m_Polygons[eLeft].SetSize(100.0f, 100.0f);

	m_Polygons[eRight].LoadTexture(InstructionsCursorRight);
	m_Polygons[eLeft].LoadTexture(InstructionsCursorLeft);
}

//=============================================================================
// 
// �I������
// 
//=============================================================================
void CInstructionsCursor::Uninit()
{
	m_Polygons.clear();
	m_TextureMoves.clear();
}

//=============================================================================
// 
// �X�V����
// 
//=============================================================================
void CInstructionsCursor::Update()
{

}

//=============================================================================
// 
// �`�揈��
// 
//=============================================================================
void CInstructionsCursor::Draw()
{
	for (int i = 0; i < eCursorMax; i++)
		m_Polygons[i].Draw();
}

//=============================================================================
// 
// �J�[�\���C��
// 
//=============================================================================
void CInstructionsCursor::MoveCursor(int index)
{

	// ���\����\���@����������
	if (index == eInstructions_Page1)
	{
		// ��\��
		m_Polygons[eRight].SetAlpha(0);
		m_Polygons[eLeft].SetAlpha(1);
	}
	if (index == eInstructions_Page2)
	{
		// ��\��
		m_Polygons[eRight].SetAlpha(1);
		m_Polygons[eLeft].SetAlpha(1);
	}
	if (index == eInstructions_Page3)
	{
		// ��\��
		m_Polygons[eRight].SetAlpha(1);
		m_Polygons[eLeft].SetAlpha(0);
	}

	m_TextureMoves[eRight].TextureRightLeft(m_Polygons[eRight], -560.0f);
	m_TextureMoves[eLeft].TextureRightLeft(m_Polygons[eLeft], 540.0f);
}
