//=============================================================================
// CPauseMenuTexture.cpp
//=============================================================================
// Author  松野 将之
//=============================================================================
#include "PauseMenuTexture.h"

//=============================================================================
// 
// コンストラクタ
// 
//=============================================================================
CPauseMenuTexture::CPauseMenuTexture()
{
	// インスタンス生成
	m_PauseMenuBackGround = std::make_shared<CPauseMenuBackGround>();
	m_PauseMenuLogo = std::make_shared<CPauseMenuLogo>();
	m_PauseMenuChoices = std::make_shared<CPauseMenuChoices>();

	// TODO リストに追加
	m_pPauseTextures.emplace_back(m_PauseMenuBackGround);
	m_pPauseTextures.emplace_back(m_PauseMenuLogo);
	m_pPauseTextures.emplace_back(m_PauseMenuChoices);
}

//=============================================================================
// 
// 初期化処理
// 
//=============================================================================
void CPauseMenuTexture::Init()
{
	for (auto& it : m_pPauseTextures)
		it->Init();
}

//=============================================================================
// 
// 終了処理
// 
//=============================================================================
void CPauseMenuTexture::Uninit()
{
	for (auto& it : m_pPauseTextures)
		it->Uninit();
}

//=============================================================================
// 
// 更新処理
// 
//=============================================================================
void CPauseMenuTexture::Update(int index)
{
	for (auto& it : m_pPauseTextures)
		it->Update();

	// 選択肢色変更
	m_PauseMenuChoices->ColorChange(index);
}

//=============================================================================
// 
// 描画処理
// 
//=============================================================================
void CPauseMenuTexture::Draw()
{
	for (auto& it : m_pPauseTextures)
		it->Draw();
}