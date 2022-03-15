//=============================================================================
// TitleMenuChoices.cpp
//=============================================================================
// Author  松野 将之
//=============================================================================
#include "TitleMenuChoices.h"
#include <Scene/Title/TitleScene.h>

//=============================================================================
// 
// 無名名前空間
// 
//=============================================================================
namespace
{
	// 各選択肢のテクスチャ
	const auto TitleMenuStart = L"data/texture/Title/Start.png";
	const auto TitleMenuEdit  = L"data/texture/Title/Edit.png";
	const auto TitleMenuExit  = L"data/texture/Title/Exit.png";
}

//=============================================================================
// 
// コンストラクタ
// 
//=============================================================================
CTitleMenuChoices::CTitleMenuChoices()
{
	m_TextureColor = std::make_unique<CTextureColorChangeComponent>();
}
//=============================================================================
// 
// 初期化処理
// 
//=============================================================================
void CTitleMenuChoices::Init()
{

	m_Polygons.resize(eTitle_Max);

	XMFLOAT2 size = XMFLOAT2(640, 80.0f);

	// 各選択肢の位置を設定
	for (int i = 0; i < eTitle_Max; i++)
	{
		m_Polygons[i].SetPosition(0.0f, 20.0f - (i * 90.0f));
		m_Polygons[i].SetSize(size);
	}
	// スタート
	m_Polygons[eTitle_Start].LoadTexture(TitleMenuStart);
	m_Polygons[eTitle_Edit].LoadTexture(TitleMenuEdit);
	m_Polygons[eTitle_Exit].LoadTexture(TitleMenuExit);
}

//=============================================================================
// 
// 終了処理
// 
//=============================================================================
void CTitleMenuChoices::Uninit()
{
	m_Polygons.clear();
}

//=============================================================================
// 
// 更新処理
// 
//=============================================================================
void CTitleMenuChoices::Update()
{
}

//=============================================================================
// 
// 引数付き更新処理
// 
//=============================================================================
void CTitleMenuChoices::MenuChoices(int index)
{
	// 選択テキスト色変更
	float color = m_TextureColor->ColorChange();

	for (int i = 0; i < eTitle_Max; i++)
	{
		if (i == index)
			m_Polygons[i].SetColor(1.0f, 1.0f, color);
		else
			m_Polygons[i].SetColor(1.0f, 1.0f, 1.0f);
	}
}

//=============================================================================
// 
// 描画処理
// 
//=============================================================================
void CTitleMenuChoices::Draw()
{
	// テクスチャ描画
	for (int i = 0; i < eTitle_Max; i++)
		m_Polygons[i].Draw();
}