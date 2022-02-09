//=============================================================================
// TitleBackGround.cpp
//=============================================================================
// Author  松野 将之
//=============================================================================
#include "TitleBackGround.h"
#include <Scene/Title/TitleScene.h>

//=============================================================================
// 
// 無名名前空間
// 
//=============================================================================
namespace
{
	constexpr int BgNum = 2; // 背景画像の数
	const auto TitleBackGround = L"data/texture/Title/TitleBackGround.png";
}

//=============================================================================
// 
// 初期化処理
// 
//=============================================================================
void CTitleBackGround::Init()
{

	m_Polygons.resize(eTitleBackGroundMax);

	// 背景
	for (int i = 0; i < BgNum; i++)
	{
		m_Polygons[i].SetPosition(0.0f, 0.0f);
		m_Polygons[i].SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
		m_Polygons[i].LoadTexture(TitleBackGround);
	}
}

//=============================================================================
// 
// 終了処理
// 
//=============================================================================
void CTitleBackGround::Uninit()
{
	m_Polygons.clear();
}

//=============================================================================
// 
// 更新処理
// 
//=============================================================================
void CTitleBackGround::Update()
{
	// 背景画像をスクロール
	static float fPosX = 0.0f;
	fPosX -= 1.0f;
	for (int i = 0; i < BgNum; i++)
	{
		m_Polygons[i].SetPosition(fPosX + (i * SCREEN_WIDTH), 0.0f);
		// 左端まで行ったら右端から再描画
		if (fPosX <= -SCREEN_WIDTH)
		{
			m_Polygons[i].SetPosition(float(i * SCREEN_WIDTH), 0.0f);
			fPosX = 0;
		}
	}
}

//=============================================================================
// 
// 描画処理
// 
//=============================================================================
void CTitleBackGround::Draw()
{
	// テクスチャ描画
	for (int i = 0; i < eTitleBackGroundMax; i++)
		m_Polygons[i].Draw();
}