//=============================================================================
// TimeLeapTexture.cpp
//=============================================================================
// Author  松野 将之
//=============================================================================
#include "TimeLeapTexture.h"

//=============================================================================
// 
// 無名名前空間
// 
//=============================================================================
namespace
{
	//const auto InstructionsBackGround = L"data/TEXTURE/GrayBackGround.png";
}
//=============================================================================
// 
// コンストラクタ
// 
//=============================================================================
CTimeLeapTexture::CTimeLeapTexture()
{
	//m_TextureFade = std::make_unique<CTextureFadeComponent>();
}

//=============================================================================
// 
// 初期化処理
// 
//=============================================================================
void CTimeLeapTexture::Init()
{
	//m_Polygon->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	//m_Polygon->SetAlpha(0);
	//m_Polygon->LoadTexture(InstructionsBackGround);
}

//=============================================================================
// 
// 終了処理
// 
//=============================================================================
void CTimeLeapTexture::Uninit()
{
}

//=============================================================================
// 
// 更新処理
// 
//=============================================================================
void CTimeLeapTexture::Update()
{
	//m_TextureFade->FadeInOut(m_Polygon, 30.0f);
}

//=============================================================================
// 
// 描画処理
// 
//=============================================================================
void CTimeLeapTexture::Draw()
{
	//m_Polygon->Draw();
}