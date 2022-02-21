//=============================================================================
// CInstructions.cpp
//=============================================================================
// Author  ���� ���V
//=============================================================================

#include "Instructions.h"
#include <System/Input/input.h>
#include <System/Sound/Sound.h>

//=============================================================================
// 
// �R���X�g���N�^
// 
//=============================================================================
CInstructions::CInstructions()
{
	// �C���X�^���X����
	m_InstructionsBackGround = std::make_shared<CInstructionsBackGround>();
	m_InstructionsCursor = std::make_shared<CInstructionsCursor>();
	m_InstructionsScreen = std::make_shared<CInstructionsScreen>();

	// ���X�g�ǉ�
	m_pInstructionsTextures.emplace_back(m_InstructionsBackGround);
	m_pInstructionsTextures.emplace_back(m_InstructionsCursor);
	m_pInstructionsTextures.emplace_back(m_InstructionsScreen);
}

//=============================================================================
// 
// ����������
// 
//=============================================================================
void CInstructions::Init()
{
	// ������
	for (auto& it : m_pInstructionsTextures)
		it->Init();
}

//=============================================================================
// 
// �I������
// 
//=============================================================================
void CInstructions::Uninit()
{	
	// �I��
	for (auto& it : m_pInstructionsTextures)
		it->Uninit();
}

//=============================================================================
// 
// �X�V����
// 
//=============================================================================
void CInstructions::Update(GameState state)
{
	// ��������ȊO�Ȃ�X�L�b�v
	if (state != GameState::eInstructions)	return;

	// �X�V
	for (auto& it : m_pInstructionsTextures)
		it->Update();

	// ��Ɨp�ϐ�
	static float fPosX = 0.0f;	 // �ʒu
	static float fMove = 0.0f;	 // �ړ���
	static int nCurrentPage = 0; // ���݂̃y�[�W
	float movment = 110.0f; // �ړ���

	// �y�[�W�ړ�
	fPosX += fMove;
	fMove += (0.0f - fMove) * 0.1f;

	// �y�[�W�؂�ւ�
	if (GetKeyTrigger(VK_A) && nCurrentPage > eInstructions_Page1)
	{
		CSound::Play(SE_SELECT_CURSOR);

		nCurrentPage--;
		fMove += movment;
	}
	if (GetKeyTrigger(VK_D) && nCurrentPage < eInstructions_Page3)
	{
		CSound::Play(SE_SELECT_CURSOR);

		nCurrentPage++;
		fMove -= movment;
	}

	// �J�[�\���ړ� ��\��
	m_InstructionsCursor->MoveCursor(nCurrentPage);

	// �y�[�W�ړ�
	m_InstructionsScreen->PageMove(fPosX);
}

//=============================================================================
// 
// �`�揈��
// 
//=============================================================================
void CInstructions::Draw(GameState state)
{
	// ��������ȊO�Ȃ�X�L�b�v
	if (state != GameState::eInstructions)	return;

	// �`��
	for (auto& it : m_pInstructionsTextures)
		it->Draw();

}
