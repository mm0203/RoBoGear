//=============================================================================
// InstructionsCursor.cpp
//=============================================================================
// Author  松野 将之
//=============================================================================

#include "InstructionsScreen.h"
#include "Instructions.h"

//=============================================================================
// 
// 無名名前空間
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
// 初期化処理
// 
//=============================================================================
void CInstructionsScreen::Init()
{
	m_Polygons.resize(eInstructions_PageMax);

	// 操作説明
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
// 終了処理
// 
//=============================================================================
void CInstructionsScreen::Uninit()
{
	m_Polygons.clear();
}

//=============================================================================
// 
// 更新処理
// 
//=============================================================================
void CInstructionsScreen::Update()
{

}

//=============================================================================
// 
// 描画処理
// 
//=============================================================================
void CInstructionsScreen::Draw()
{
	for (int i = 0; i < eInstructions_PageMax; i++)
		m_Polygons[i].Draw();
}

//=============================================================================
// 
// カーソル修飾
// 
//=============================================================================
void CInstructionsScreen::PageMove(float& move)
{
	// 画像のポジションを変更
	for (int i = 0; i < eInstructions_PageMax; i++)
		m_Polygons[i].SetPosition(move + (i * 1100), 0.0f);
}
