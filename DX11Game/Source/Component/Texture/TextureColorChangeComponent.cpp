//=============================================================================
// CTextureColorChangeComponent.cpp
//=============================================================================
// Author  松野 将之
//=============================================================================
#include "TextureColorChangeComponent.h"
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>

//=============================================================================
// 
// コンストラクタ
// 
//=============================================================================
CTextureColorChangeComponent::CTextureColorChangeComponent()
{
	m_nTime = 0;
	m_fColor = 0.0f;
}

//=============================================================================
// 
// テクスチャ色変更
// 
//=============================================================================
float CTextureColorChangeComponent::ColorChange(int speed)
{
	// 色の変更速度
	m_nTime += speed;
	m_fColor = abs(sinf(m_nTime * (float)M_PI / 100.0f));
	return m_fColor;
}