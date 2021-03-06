//=============================================================================
// CTitleCubeObj.cpp
//=============================================================================
// Author  松野 将之
//=============================================================================
#include "TitleCubeObj.h"

#define MODEL_TITLE_CUBE  "data/MODEL/Object/FallBrock/FallBrock.fbx"

//=============================================================================
// 
// 無名名前空間
// 
//=============================================================================
namespace
{
	constexpr float Move = 1.0f; // 移動量
	constexpr float EndCubePos = 495.0f; // キューブの左端描画限界
}

//=============================================================================
// 
// 初期化処理
// 
//=============================================================================
void CTitleCubeObj::Init()
{
	m_Model.LoadModel(MODEL_TITLE_CUBE);
}

//=============================================================================
// 
// 更新処理
// 
//=============================================================================
void CTitleCubeObj::Update()
{
	m_Pos.x -= Move;

	// 左端まで行ったら右から再描画
	if (m_Pos.x < -EndCubePos)
		m_Pos.x = EndCubePos;
}