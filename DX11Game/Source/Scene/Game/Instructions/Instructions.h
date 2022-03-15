//=============================================================================
// Instructions.h
//=============================================================================
// Author  ���� ���V
//=============================================================================
#pragma once

#include <Manager/Sprite.h>
#include "InstructionsBackGround.h"
#include "InstructionsCursor.h"
#include "InstructionsScreen.h"
#include <list>
//=============================================================================
// 
// �}�N����`
// 
//=============================================================================
enum InstructionsPage
{
	eInstructions_Page1 = 0,
	eInstructions_Page2,
	eInstructions_Page3,
	eInstructions_PageMax
};

//=============================================================================
// 
// �N���X��`
// 
//=============================================================================
class CInstructions : public CSprite
{
public:
	CInstructions();
	~CInstructions() = default;

	void Init()   override;
	void Uninit() override;
	void Update(GameState state) override;
	void Draw(GameState state)   override;

private:
	// �w�i
	std::shared_ptr<CInstructionsBackGround> m_InstructionsBackGround;
	// �J�[�\��
	std::shared_ptr<CInstructionsCursor> m_InstructionsCursor;
	// ��������̉摜
	std::shared_ptr<CInstructionsScreen> m_InstructionsScreen;

private:
	std::list<tex_shared> m_pInstructionsTextures;
};

