//=============================================================================
// CTextureMoveComponent.cpp
//=============================================================================
// Author  松野 将之
//=============================================================================
#include "TextureMoveComponent.h"
#include <math.h>

//=============================================================================
// 
// コンストラクタ
// 
//=============================================================================
CTextureMoveComponent::CTextureMoveComponent()
{
	m_nTime = 0;
	m_TextMove = 0.0f;
}

//=============================================================================
// 
// テクスチャ上下移動
// 
//=============================================================================
void CTextureMoveComponent::TextureUpDown(CPolygon& polygon, float posY)
{
	m_nTime += 3;
	m_TextMove += ((sinf(m_nTime * 3.1415f / 100)));
	polygon.SetPosition(0.0f,m_TextMove + posY);
}

//=============================================================================
// 
// テクスチャ上下移動
// 
//=============================================================================
void CTextureMoveComponent::TextureUpDown(std::shared_ptr<CPolygon>& polygon, float posY)
{
	m_nTime += 3;
	m_TextMove += ((sinf(m_nTime * 3.1415f / 100)));
	polygon->SetPosition(0.0f, m_TextMove + posY);
}

//=============================================================================
// 
// テクスチャ左右移動
// 
//=============================================================================
void CTextureMoveComponent::TextureRightLeft(CPolygon& polygon, float posX)
{
	m_nTime += 3;
	m_TextMove += ((sinf(m_nTime * 3.1415f / 100)));
	polygon.SetPosition(m_TextMove + posX, 0.0f);
}