//=============================================================================
// Trap.cpp
//=============================================================================
// Author  松野 将之
//=============================================================================
#include "Trap.h"
#include <Renderer/Effect/Effect.h>
#include <Manager/GameManager.h>

//=============================================================================
// 
// コンストラクタ
// 
//=============================================================================
CTrap::CTrap()
{
	m_tag = TagTrap;
	m_Model.LoadModel(MODEL_TRAP);
	m_nCount = 0;
}

//=============================================================================
// 
// 初期化処理
// 
//=============================================================================
void CTrap::Init()
{

}

//=============================================================================
// 
// 更新処理
// 
//=============================================================================
void CTrap::Update()
{
	m_nCount++;
	// 一定時間(３秒)でエフェクト発生
	if (m_nCount >= Second * 3)
	{
		CEffectManager::CreateEffect(Effect_Trap, m_Pos);
		m_nCount = 0;
	}
}

