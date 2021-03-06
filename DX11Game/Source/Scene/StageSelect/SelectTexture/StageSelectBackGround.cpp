//=============================================================================
// StageBackGround.cpp
//=============================================================================
// Author  松野 将之
//=============================================================================
#include "StageSelectBackGround.h"

//=============================================================================
// 
// 無名名前空間
// 
//=============================================================================
namespace
{
	const auto StageSelectBackGround = L"data/texture/StageSelect/SelectBg.png";
}

//=============================================================================
// 
// 初期化処理
// 
//=============================================================================
void CStageSelectBackGround::Init()
{
	// 背景
	m_Polygon->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_Polygon->LoadTexture(StageSelectBackGround);
}

//=============================================================================
// 
// 終了処理
// 
//=============================================================================
void CStageSelectBackGround::Uninit()
{
}

//=============================================================================
// 
// 更新処理
// 
//=============================================================================
void CStageSelectBackGround::Update()
{
}

//=============================================================================
// 
// 描画処理
// 
//=============================================================================
void CStageSelectBackGround::Draw()
{
	m_Polygon->Draw();
}