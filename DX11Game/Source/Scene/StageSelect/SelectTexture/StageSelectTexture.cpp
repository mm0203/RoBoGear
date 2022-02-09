//=============================================================================
// StageSelectTexture.cpp
//=============================================================================
// Author  松野 将之
//=============================================================================
#include "StageSelectTexture.h"

//=============================================================================
// 
// コンストラクタ
// 
//=============================================================================
CStageSelectTexture::CStageSelectTexture()
{
	// インスタンス生成
	m_StageSelectBackGround = std::make_shared<CStageSelectBackGround>();
	m_StageSelectLogo = std::make_shared<CStageSelectLogo>();
	m_StageSelectLevel = std::make_shared<CStageSelectLevel>();
	m_StageSelectCursor = std::make_shared<CStageSelectCursor>();

	// TODO リスト追加
	m_pStageSelectTextures.emplace_back(m_StageSelectBackGround);
	m_pStageSelectTextures.emplace_back(m_StageSelectLogo);
	m_pStageSelectTextures.emplace_back(m_StageSelectLevel);
	m_pStageSelectTextures.emplace_back(m_StageSelectCursor);
}

//=============================================================================
// 
// 初期化処理
// 
//=============================================================================
void CStageSelectTexture::Init()
{
	for (auto& it : m_pStageSelectTextures)
		it->Init();
}

//=============================================================================
// 
// 終了処理
// 
//=============================================================================
void CStageSelectTexture::Uninit()
{
	for (auto& it : m_pStageSelectTextures)
		it->Uninit();
}

//=============================================================================
// 
// 更新処理
// 
//=============================================================================
void CStageSelectTexture::Update(int index)
{
	for (auto& it : m_pStageSelectTextures)
		it->Update();

	// テクスチャ変更
	m_StageSelectCursor->TextureChage(index);

}

//=============================================================================
// 
// 描画処理
// 
//=============================================================================
void CStageSelectTexture::Draw()
{
	for (auto& it : m_pStageSelectTextures)
		it->Draw();
}