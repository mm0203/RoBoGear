//=============================================================================
// Cube.cpp
//=============================================================================
// Author  松野 将之
//=============================================================================
#include "Cube.h"

//=============================================================================
// 
// コンストラクタ
// 
//=============================================================================
CCube::CCube()
{
	m_tag = TagCube;
	m_Model.LoadModel(MODEL_CUBE);
}

//=============================================================================
// 
// 初期化処理
// 
//=============================================================================
void CCube::Init()
{
}

//=============================================================================
// 
// 更新処理
// 
//=============================================================================
void CCube::Update()
{
	// 移動
	ObjectMove();
}