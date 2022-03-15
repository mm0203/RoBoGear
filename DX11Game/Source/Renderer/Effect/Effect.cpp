//=============================================================================
// Effect.cpp
//=============================================================================
// Author  松野 将之
//=============================================================================

#include "Effect.h"

//=============================================================================
// 
// 初期化処理
// 
//=============================================================================
void CEffect::Init()
{
	m_FrameNum = XMINT2(1, 1);
	m_MaxAnimNum = 0;
	m_CurrentAnimNum = 0;

	CBillBoard::Init();
}

//=============================================================================
// 
// 終了処理
// 
//=============================================================================
void CEffect::Uninit()
{
	CBillBoard::Uninit();
}

//=============================================================================
// 
// 更新処理
// 
//=============================================================================
void CEffect::Update()
{
	if (++m_SpeedCount >= m_Speed)
	{
		// エフェクトが最大アニメ数を超えたら削除
		if (m_CurrentAnimNum++ > m_MaxAnimNum)
		{
			CEffectManager::DeleteObject(this);
		}
		m_SpeedCount = 0;
	}

	CBillBoard::Update();
}

//=============================================================================
// 
// 描画処理
// 
//=============================================================================
void CEffect::Draw()
{
	CBillBoard::Draw(m_CurrentAnimNum);
}


