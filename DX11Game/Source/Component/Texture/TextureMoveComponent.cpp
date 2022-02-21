//=============================================================================
// CTextureMoveComponent.cpp
//=============================================================================
// Author  ���� ���V
//=============================================================================
#include "TextureMoveComponent.h"
#define _USE_MATH_DEFINES
#include <math.h>

//=============================================================================
// 
// �R���X�g���N�^
// 
//=============================================================================
CTextureMoveComponent::CTextureMoveComponent()
{
	m_nTime = 0;
	m_TextMove = 0.0f;
}

//=============================================================================
// 
// �e�N�X�`���㉺�ړ�
// 
//=============================================================================
void CTextureMoveComponent::TextureUpDown(CPolygon& polygon, float posY, int speed)
{
	m_nTime += speed;
	m_TextMove += ((sinf(m_nTime * (float)M_PI / 100.0f)));
	polygon.SetPosition(0.0f,m_TextMove + posY);
}

//=============================================================================
// 
// �e�N�X�`���㉺�ړ�
// 
//=============================================================================
void CTextureMoveComponent::TextureUpDown(std::shared_ptr<CPolygon>& polygon, float posY, int speed)
{
	m_nTime += speed;
	m_TextMove += ((sinf(m_nTime * (float)M_PI / 100.0f)));
	polygon->SetPosition(0.0f, m_TextMove + posY);
}

//=============================================================================
// 
// �e�N�X�`�����E�ړ�
// 
//=============================================================================
void CTextureMoveComponent::TextureRightLeft(CPolygon& polygon, float posX, int speed)
{
	m_nTime += speed;
	m_TextMove += ((sinf(m_nTime * (float)M_PI / 100.0f)));
	polygon.SetPosition(m_TextMove + posX, 0.0f);
}