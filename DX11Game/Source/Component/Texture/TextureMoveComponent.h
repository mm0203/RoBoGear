//=============================================================================
// CTextureMoveComponent.h
//=============================================================================
// Author  ���� ���V
//=============================================================================
#pragma once

#include <Renderer/Polygon/CPolygon.h>

//=============================================================================
// 
// �N���X��`
// 
//=============================================================================
class CTextureMoveComponent
{
public:
	CTextureMoveComponent();
	~CTextureMoveComponent() = default;

	void TextureUpDown(CPolygon& polygon, float posY = 0.0f, int speed = 3);
	void TextureUpDown(std::shared_ptr<CPolygon>& polygon, float posY = 0.0f, int speed = 3);
	void TextureRightLeft(CPolygon& polygon, float posX = 0.0f, int speed = 3);

private:
	int m_nTime;		// �J�E���g
	float m_TextMove;	// �e�N�X�`���ړ�
};