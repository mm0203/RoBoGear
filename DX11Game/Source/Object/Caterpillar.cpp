//=============================================================================
// Caterpillar.cpp
//=============================================================================
// Author  松野 将之
//=============================================================================
#include "Caterpillar.h"
#include <Manager/ObjectManager.h>

#define MODEL_CATERPILLAR "data/model/Object/MainAnim_Blender/Caterpillar_Anim.fbx"

//=============================================================================
// 
// コンストラクタ
// 
//=============================================================================
CCaterpillar::CCaterpillar()
{
	m_tag = "Caterpillar";
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
// \
// 更新処理
// 
//=============================================================================
void CCaterpillar::Update()
{
	const auto& player = ObjectManager::SearchObjectTag("Player");
	m_Pos = player.lock()->GetPos();
	m_Scale = player.lock()->GetScale();
	m_Rot = player.lock()->GetRot();
}
