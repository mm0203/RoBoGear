//=============================================================================
// CTextureColorChangeComponent.cpp
//=============================================================================
// Author  ���� ���V
//=============================================================================
#include "TextureColorChangeComponent.h"
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>

//=============================================================================
// 
// �R���X�g���N�^
// 
//=============================================================================
CTextureColorChangeComponent::CTextureColorChangeComponent()
{
	m_nTime = 0;
	m_fColor = 0.0f;
}

//=============================================================================
// 
// �e�N�X�`���F�ύX
// 
//=============================================================================
float CTextureColorChangeComponent::ColorChange(int speed)
{
	// �F�̕ύX���x
	m_nTime += speed;
	m_fColor = abs(sinf(m_nTime * (float)M_PI / 100.0f));
	return m_fColor;
}