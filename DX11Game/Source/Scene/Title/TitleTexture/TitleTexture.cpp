//=============================================================================
// CTitleTexture.cpp
//=============================================================================
// Author  松野 将之
//=============================================================================
#include "TitleTexture.h"


//=============================================================================
// 
// コンストラクタ
// 
//=============================================================================
CTitleTexture::CTitleTexture()
{
	// インスタンス生成
	m_TitleBackGround = std::make_shared<CTitleBackGround>();
	m_TitleFrame = std::make_shared<CTitleFrame>();
	m_TitleMenuChoices = std::make_shared<CTitleMenuChoices>();
	m_TitleLogo = std::make_shared<CTitleLogo>();

	// リスト追加
	m_pTitleTextures.emplace_back(m_TitleBackGround);
	m_pTitleTextures.emplace_back(m_TitleFrame);
	m_pTitleTextures.emplace_back(m_TitleMenuChoices);
	m_pTitleTextures.emplace_back(m_TitleLogo);
}

//=============================================================================
// 
// 初期化処理
// 
//=============================================================================
void CTitleTexture::Init()
{
	// 初期化
	for (auto& it : m_pTitleTextures)
		it->Init();
}

//=============================================================================
// 
// 終了処理
// 
//=============================================================================
void CTitleTexture::Uninit()
{
	// 終了
	for (auto& it : m_pTitleTextures)
		it->Uninit();
}

//=============================================================================
// 
// 更新処理
// 
//=============================================================================
void CTitleTexture::Update(int index)
{
	// 更新
	for (auto& it : m_pTitleTextures)
		it->Update();

	m_TitleMenuChoices->MenuChoices(index);
}

//=============================================================================
// 
// 描画処理
// 
//=============================================================================
void CTitleTexture::Draw()
{
	// 描画
	for (auto& it : m_pTitleTextures)
		it->Draw();
}