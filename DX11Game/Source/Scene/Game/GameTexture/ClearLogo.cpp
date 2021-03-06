//=============================================================================
// ClearLogo.cpp
//=============================================================================
// Author  松野 将之
//=============================================================================
#include "ClearLogo.h"

#define CLEAR_LOGO "data/texture/UI/clear.png"

//=============================================================================
// 
// 無名名前空間
// 
//=============================================================================
namespace
{
	const auto ClearLogo = L"data/texture/UI/clear.png";
}

//=============================================================================
// 
// コンストラクタ
// 
//=============================================================================
CClearLogo::CClearLogo()
{
	m_TextureMove = std::make_unique<CTextureMoveComponent>();
	m_TextureFade = std::make_unique<CTextureFadeComponent>();
}

//=============================================================================
// 
// 初期化処理
// 
//=============================================================================
void CClearLogo::Init()
{
	m_Polygon->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_Polygon->SetAlpha(0);	// 最初は非表示
	m_Polygon->LoadTexture(ClearLogo);
}

//=============================================================================
// 
// 終了処理
// 
//=============================================================================
void CClearLogo::Uninit()
{
}

//=============================================================================
// 
// 更新処理
// 
//=============================================================================
void CClearLogo::Update()
{
	// テキスト上下
	m_TextureMove->TextureUpDown(m_Polygon);
	// テキストフェードイン
	m_TextureFade->FadeIn(m_Polygon);
}

//=============================================================================
// 
// 描画処理
// 
//=============================================================================
void CClearLogo::Draw()
{
	m_Polygon->Draw();
}