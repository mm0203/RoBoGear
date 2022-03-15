//=============================================================================
// InstructionsCursor.cpp
//=============================================================================
// Author  松野 将之
//=============================================================================

#include "InstructionsCursor.h"
#include "Instructions.h"

//=============================================================================
// 
// 無名名前空間
// 
//=============================================================================
namespace
{
	const auto InstructionsCursorRight = L"data/texture/Instructions/CursorA.png";
	const auto InstructionsCursorLeft  = L"data/texture/Instructions/CursorD.png";
}

//=============================================================================
// 
// 初期化処理
// 
//=============================================================================
void CInstructionsCursor::Init()
{
	m_Polygons.resize(eCursorMax);
	m_TextureMoves.resize(eCursorMax);

	// カーソル
	m_Polygons[eRight].SetSize(100.0f, 100.0f);
	m_Polygons[eLeft].SetSize(100.0f, 100.0f);

	m_Polygons[eRight].LoadTexture(InstructionsCursorRight);
	m_Polygons[eLeft].LoadTexture(InstructionsCursorLeft);
}

//=============================================================================
// 
// 終了処理
// 
//=============================================================================
void CInstructionsCursor::Uninit()
{
	m_Polygons.clear();
	m_TextureMoves.clear();
}

//=============================================================================
// 
// 更新処理
// 
//=============================================================================
void CInstructionsCursor::Update()
{

}

//=============================================================================
// 
// 描画処理
// 
//=============================================================================
void CInstructionsCursor::Draw()
{
	for (int i = 0; i < eCursorMax; i++)
		m_Polygons[i].Draw();
}

//=============================================================================
// 
// カーソル修飾
// 
//=============================================================================
void CInstructionsCursor::MoveCursor(int index)
{

	// カーソル表示非表示　いいやり方じゃない
	if (index == eInstructions_Page1)
	{
		m_Polygons[eRight].SetAlpha(0);
		m_Polygons[eLeft].SetAlpha(1);
	}
	if (index == eInstructions_Page2)
	{
		m_Polygons[eRight].SetAlpha(1);
		m_Polygons[eLeft].SetAlpha(1);
	}
	if (index == eInstructions_Page3)
	{
		m_Polygons[eRight].SetAlpha(1);
		m_Polygons[eLeft].SetAlpha(0);
	}

	// 左右移動
	m_TextureMoves[eRight].TextureRightLeft(m_Polygons[eRight], -560.0f);
	m_TextureMoves[eLeft].TextureRightLeft(m_Polygons[eLeft], 540.0f);
}
