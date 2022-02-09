//=============================================================================
// InstructionsCursor.cpp
//=============================================================================
// Author  ���� ���V
//=============================================================================

#include "InstructionsScreen.h"
#include "Instructions.h"

//=============================================================================
// 
// �������O���
// 
//=============================================================================
namespace
{
	const auto InstructionsPage1 = L"data/texture/Instructions/Instructions1.png";
	const auto InstructionsPage2 = L"data/texture/Instructions/Instructions2.png";
	const auto InstructionsPage3 = L"data/texture/Instructions/Instructions3.png";
}

//=============================================================================
// 
// ����������
// 
//=============================================================================
void CInstructionsScreen::Init()
{
	m_Polygons.resize(eInstructions_PageMax);

	// �������
	for (int i = 0; i < eInstructions_PageMax; i++)
	{
		m_Polygons[i].SetPosition(0.0f + (i * 1100), 0.0f);
		m_Polygons[i].SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	}

	m_Polygons[eInstructions_Page1].LoadTexture(InstructionsPage1);
	m_Polygons[eInstructions_Page2].LoadTexture(InstructionsPage2);
	m_Polygons[eInstructions_Page3].LoadTexture(InstructionsPage3);
}

//=============================================================================
// 
// �I������
// 
//=============================================================================
void CInstructionsScreen::Uninit()
{
	m_Polygons.clear();
}

//=============================================================================
// 
// �X�V����
// 
//=============================================================================
void CInstructionsScreen::Update()
{

}

//=============================================================================
// 
// �`�揈��
// 
//=============================================================================
void CInstructionsScreen::Draw()
{
	for (int i = 0; i < eInstructions_PageMax; i++)
		m_Polygons[i].Draw();
}

//=============================================================================
// 
// �J�[�\���C��
// 
//=============================================================================
void CInstructionsScreen::PageMove(float& move)
{
	// �摜�̃|�W�V������ύX
	for (int i = 0; i < eInstructions_PageMax; i++)
		m_Polygons[i].SetPosition(move + (i * 1100), 0.0f);
}
