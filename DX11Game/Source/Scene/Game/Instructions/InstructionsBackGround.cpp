//=============================================================================
// InstructionsBackGround.cpp
//=============================================================================
// Author  松野 将之
//=============================================================================

#include "InstructionsBackGround.h"

//=============================================================================
// 
// 無名名前空間
// 
//=============================================================================
namespace
{
	const auto InstructionsBackGround = L"data/TEXTURE/GrayBackGround.png";
}

//=============================================================================
// 
// 初期化処理
// 
//=============================================================================
void CInstructionsBackGround::Init()
{
	// 背景
	m_Polygon->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_Polygon->SetAlpha(0.7f); // ゲーム画面をやや不透明に
	m_Polygon->LoadTexture(InstructionsBackGround);
}

//=============================================================================
// 
// 終了処理
// 
//=============================================================================
void CInstructionsBackGround::Uninit()
{
}

//=============================================================================
// 
// 更新処理
// 
//=============================================================================
void CInstructionsBackGround::Update()
{
}

//=============================================================================
// 
// 描画処理
// 
//=============================================================================
void CInstructionsBackGround::Draw()
{
	m_Polygon->Draw();
}
