//=============================================================================
// CTextureMoveComponent.cpp
//=============================================================================
// Author  ���� ���V
//=============================================================================
#include "TextureMoveComponent.h"
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
void CTextureMoveComponent::TextureUpDown(CPolygon& polygon, float posY)
{
	m_nTime += 3;
	m_TextMove += ((sinf(m_nTime * 3.1415f / 100)));
	polygon.SetPosition(0.0f,m_TextMove + posY);
}

//=============================================================================
// 
// �e�N�X�`���㉺�ړ�
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
// �e�N�X�`�����E�ړ�
// 
//=============================================================================
void CTextureMoveComponent::TextureRightLeft(CPolygon& polygon, float posX)
{
	m_nTime += 3;
	m_TextMove += ((sinf(m_nTime * 3.1415f / 100)));
	polygon.SetPosition(m_TextMove + posX, 0.0f);
}