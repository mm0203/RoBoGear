//=============================================================================
// CKey.cpp
//=============================================================================
// Author  松野 将之
//=============================================================================
#include "key.h"

//=============================================================================
// 
// コンストラクタ
// 
//=============================================================================
CKey::CKey()
{
	m_tag = TagKey;
	m_Model.LoadModel(MODEL_KEY);
}

//=============================================================================
// 
// 初期化処理
// 
//=============================================================================
void CKey::Init()
{

}

//=============================================================================
// 
// 更新処理
// 
//=============================================================================
void CKey::Update()
{
	// 回転速度
	float RatateSpeed = 2.5f;

	// 回転
	m_Rot.y += RatateSpeed;

	// 180度回転したらY座標をリセット
	if (m_Rot.y >= 180.0f)	
		m_Rot.y -= 360.0f;
}
