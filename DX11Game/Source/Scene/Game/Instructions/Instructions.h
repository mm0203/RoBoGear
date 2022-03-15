//=============================================================================
// Instructions.h
//=============================================================================
// Author  松野 将之
//=============================================================================
#pragma once

#include <Manager/Sprite.h>
#include "InstructionsBackGround.h"
#include "InstructionsCursor.h"
#include "InstructionsScreen.h"
#include <list>
//=============================================================================
// 
// マクロ定義
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
// クラス定義
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
	// 背景
	std::shared_ptr<CInstructionsBackGround> m_InstructionsBackGround;
	// カーソル
	std::shared_ptr<CInstructionsCursor> m_InstructionsCursor;
	// 操作説明の画像
	std::shared_ptr<CInstructionsScreen> m_InstructionsScreen;

private:
	std::list<tex_shared> m_pInstructionsTextures;
};

