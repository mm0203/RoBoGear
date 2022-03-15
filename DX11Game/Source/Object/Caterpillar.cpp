//=============================================================================
// Caterpillar.cpp
//=============================================================================
// Author  松野 将之
//=============================================================================
#include "Caterpillar.h"
#include <Manager/ObjectManager.h>
#include "Player.h"

#define MODEL_CATERPILLAR "data/model/Object/MainAnim_Blender/Caterpillar_Anim.fbx"

//=============================================================================
// 
// コンストラクタ
// 
//=============================================================================
CCaterpillar::CCaterpillar()
{
	m_tag = TagCaterpillar;
	m_Model.LoadModel(MODEL_CATERPILLAR);
}

//=============================================================================
// 
// 初期化処理
// 
//=============================================================================
void CCaterpillar::Init()
{

}

//=============================================================================
// 
// 更新処理
// 
//=============================================================================
void CCaterpillar::Update()
{
	// プレイヤーの座標と同じ場所に
	const auto& player = CObjectManager::SearchObjectTag(TagPlayer);
	m_Pos = player.lock()->GetPos();
	m_Scale = player.lock()->GetScale();
	m_Rot = player.lock()->GetRot();
}
