//=============================================================================
// GameBackGround.cpp
//=============================================================================
// Author  松野 将之
//=============================================================================
#include "GameBackGround.h"
#include <Manager/GameManager.h>

//=============================================================================
// 
// 無名名前空間
// 
//=============================================================================
namespace
{
	// TODO cppわけるべき？
	const auto GameOperation = L"data/texture/UI/OperationUI.png";
	const auto BackGroundFrame = L"data/texture/UI/Frame.png";
}

//=============================================================================
// 
// コンストラクタ
// 
//=============================================================================
CGameBackGround::CGameBackGround()
{
	m_fAngle = 0.0f;
}

//=============================================================================
// 
// 初期化処理
// 
//=============================================================================
void CGameBackGround::Init()
{
	// サイズ確保
	m_Polygons.resize(GameNotmoveTextureMax);
	m_TextureFades.resize(GameNotmoveTextureMax);

	// 各フェードα値を1に
	for(int i = 0;i < GameNotmoveTextureMax; i++)
	m_TextureFades[i].SetAlpha(1.0f);

	for (int i = 0; i < GameNotmoveTextureMax; i++)
		m_Polygons[i].SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	m_Polygons[eOperation].LoadTexture(GameOperation);
	m_Polygons[eBackGroundFrame].LoadTexture(BackGroundFrame);
}

//=============================================================================
// 
// 終了処理
// 
//=============================================================================
void CGameBackGround::Uninit()
{
	m_Polygons.clear();
	m_TextureFades.clear();
}

//=============================================================================
// 
// 更新処理
// 
//=============================================================================
void CGameBackGround::Update()
{
}

//=============================================================================
// 
// 描画処理
// 
//=============================================================================
void CGameBackGround::Draw()
{
	// UI描画
	for (int i = 0; i < GameNotmoveTextureMax; i++)
		m_Polygons[i].Draw();
}

//=============================================================================
// 
// フェードアウト
// 
//=============================================================================
void CGameBackGround::FadeOut()
{
	for (int i = 0; i < GameNotmoveTextureMax; i++)
		m_TextureFades[i].FadeOut(m_Polygons[i]);
}