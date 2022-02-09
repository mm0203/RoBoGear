//=============================================================================
// TitleFrame.cpp
//=============================================================================
// Author  松野 将之
//=============================================================================
#include "TitleFrame.h"
#include "TitleTexture.h"

//=============================================================================
// 
// 無名名前空間
// 
//=============================================================================
namespace
{
	const auto TitleFrame = L"data/texture/Title/titleGear.png";
}

//=============================================================================
// 
// 初期化処理
// 
//=============================================================================
void CTitleFrame::Init()
{
	// タイトル
	m_Polygon->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_Polygon->LoadTexture(TitleFrame);
}

//=============================================================================
// 
// 終了処理
// 
//=============================================================================
void CTitleFrame::Uninit()
{
}

//=============================================================================
// 
// 更新処理
// 
//=============================================================================
void CTitleFrame::Update()
{
}

//=============================================================================
// 
// 描画処理
// 
//=============================================================================
void CTitleFrame::Draw()
{
	m_Polygon->Draw();
}