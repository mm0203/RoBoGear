//=============================================================================
// StageSelectCursor.cpp
//=============================================================================
// Author  松野 将之
//=============================================================================
#include "StageSelectCursor.h"
#include <Manager/StageManager.h>

//=============================================================================
// 
// 無名名前空間
// 
//=============================================================================
namespace
{
	const auto StageSelectCursor = L"data/texture/StageSelect/cursor.png";
	const auto StageSelectCursorTitle = L"data/texture/StageSelect/selectCursorTitle.png";
}

//=============================================================================
// 
// コンストラクタ
// 
//=============================================================================
CStageSelectCursor::CStageSelectCursor()
{
	m_TextureColor = std::make_shared<CTextureColorChangeComponent>();
}

//=============================================================================
// 
// 初期化処理
// 
//=============================================================================
void CStageSelectCursor::Init()
{
	// カーソル初期化
	m_Polygon->SetPosition(0, 100.0f);
	m_Polygon->SetSize(160.0f, 160.0f);
	m_Polygon->LoadTexture(StageSelectCursor);

	// レベル初期化
	m_StageSelectLevel.Init();
}

//=============================================================================
// 
// 終了処理
// 
//=============================================================================
void CStageSelectCursor::Uninit()
{
	// レベル終了
	m_StageSelectLevel.Uninit();
}

//=============================================================================
// 
// 更新処理
// 
//=============================================================================
void CStageSelectCursor::Update()
{
	// レベル更新
	m_StageSelectLevel.Update();

	// レベルの数値に合わせた位置とサイズを取得
	m_Polygon->SetPosition(m_StageSelectLevel.GetLevelPos());
	m_Polygon->SetSize(m_StageSelectLevel.GetLevelSize());

	// カーソル色変更
	float color = m_TextureColor->ColorChange();
	m_Polygon->SetColor(0.0f, color, color);
}

//=============================================================================
// 
// 描画処理
// 
//=============================================================================
void CStageSelectCursor::Draw()
{
	// レベル描画
	m_StageSelectLevel.Draw();
	// カーソル描画
	m_Polygon->Draw();
}

//=============================================================================
// 
// テクスチャ変更
// 
//=============================================================================
void CStageSelectCursor::TextureChage(int index)
{
	// カーソルのテクスチャ変更
	if (index == eTitleBack)
		m_Polygon->LoadTexture(StageSelectCursorTitle);
	else
		m_Polygon->LoadTexture(StageSelectCursor);
}