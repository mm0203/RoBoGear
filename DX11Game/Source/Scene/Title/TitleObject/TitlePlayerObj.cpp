//=============================================================================
// CTitlePlayerObj.cpp
//=============================================================================
// Author  松野 将之
//=============================================================================
#include "TitlePlayerObj.h"
#include <Object/Player.h>

//=============================================================================
// 
// コンストラクタ
// 
//=============================================================================
CTitlePlayerObj::CTitlePlayerObj()
{
	m_tag = TagPlayer;
}
//=============================================================================
// 
// 初期化処理
// 
//=============================================================================
void CTitlePlayerObj::Init()
{
	//// モデル読み込み
	m_Model.LoadModel(MODEL_PLAYER);
	m_Caterpillar = CObjectManager::CreateObject<CCaterpillar>();
	m_Gear = CObjectManager::CreateObject<CGear>();
	m_Generare = CObjectManager::CreateObject<CGenerare>();

	//// アニメNo初期化
	m_Model.SetAnimeNo((int)PlayerAnime::eNone);
	m_Caterpillar->GetModel().SetAnimeNo((int)CaterpillarAnime::eMove);
	m_Gear->GetModel().SetAnimeNo((int)GearAnime::eMove);
	m_Generare->GetModel().SetAnimeNo((int)GenerareAnime::eMove);
}

//=============================================================================
// 
// 更新処理
// 
//=============================================================================
void CTitlePlayerObj::Update()
{
	// アニメ再生時間を取得
	CRenderer::AnimePlayTime();
}