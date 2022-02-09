//=============================================================================
// StartLogo.cpp
//=============================================================================
// Author  松野 将之
//=============================================================================
#include "StartLogo.h"
#include <Manager/GameManager.h>
#include <Scene/StageSelect/StageSelectScene.h>
#include <Manager/StageManager.h>
#include <math.h>

//=============================================================================
// 
// 無名名前空間
// 
//=============================================================================
namespace
{
	const auto StageLogo = L"data/texture/UI/StartLogo.png";
	const auto StageNumber = L"data/texture/UI/StartNumber.png";
}

//=============================================================================
// 
// コンストラクタ
// 
//=============================================================================
CStartLogo::CStartLogo()
{
	m_TextureMove = std::make_unique<CTextureMoveComponent>();
	m_nTime = 0;
	m_TextMove = 0.0f;
}

//=============================================================================
// 
// 初期化処理
// 
//=============================================================================
void CStartLogo::Init()
{
	m_TextureFades.resize(eStartLogoMax);

	// スタートテクスチャ
	m_Polygon->SetSize(SCREEN_WIDTH, 500.0f);
	m_Polygon->SetAlpha(0);	// 最初は非表示
	m_Polygon->LoadTexture(StageLogo);

	// ナンバー
	m_Number.Init(StageNumber);
}

//=============================================================================
// 
// 終了処理
// 
//=============================================================================
void CStartLogo::Uninit()
{
	// ナンバー終了
	m_Number.Uninit();
}

//=============================================================================
// 
// 更新処理
// 
//=============================================================================
void CStartLogo::Update()
{
	bool FadeState = m_TextureFades[eStartLogo].GetFadeState();

	if (FadeState)
	{
		// テキスト上下
		m_nTime += 3;
		m_TextMove += ((sinf(m_nTime * 3.1415f / 100)));
		m_TextureMove->TextureUpDown(m_Polygon);
		// テキストフェードインアウト
		m_TextureFades[eStartLogo].FadeInOut(m_Polygon);
		m_TextureFades[eStartNumber].FadeInOut(m_Number.GetPolygon());
	}
}

//=============================================================================
// 
// 描画処理
// 
//=============================================================================
void CStartLogo::Draw()
{
	m_Polygon->Draw();
	//int StageNumber = StageManager::GetStageNumber();
	int StageNumber = CGameManager::GetStageMenu();
	XMFLOAT2 pos = { 300, m_TextMove };
	// ナンバー描画
	m_Number.Draw(StageNumber + 1,pos);
}
