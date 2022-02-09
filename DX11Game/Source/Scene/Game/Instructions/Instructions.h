//=============================================================================
// Instructions.h
//=============================================================================
// Author  èºñÏ è´îV
//=============================================================================
#pragma once

#include <Manager/Sprite.h>
#include "InstructionsBackGround.h"
#include "InstructionsCursor.h"
#include "InstructionsScreen.h"
#include <list>

enum InstructionsPage
{
	eInstructions_Page1 = 0,
	eInstructions_Page2,
	eInstructions_Page3,
	eInstructions_PageMax
};

//=============================================================================
// 
// ÉNÉâÉXíËã`
// 
//=============================================================================
class CInstructions : public Sprite
{
public:
	CInstructions();
	~CInstructions() = default;

	void Init()   override;
	void Uninit() override;
	void Update(GameState state) override;
	void Draw(GameState state)   override;

private:
	std::shared_ptr<CInstructionsBackGround> m_InstructionsBackGround;
	std::shared_ptr<CInstructionsCursor> m_InstructionsCursor;
	std::shared_ptr<CInstructionsScreen> m_InstructionsScreen;

private:
	std::list<tex_shared> m_pInstructionsTextures;
};

