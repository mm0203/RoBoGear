//=============================================================================
// CTextureColorChangeComponent.h
//=============================================================================
// Author  ���� ���V
//=============================================================================
#pragma once

//=============================================================================
// 
// �N���X��`
// 
//=============================================================================
class CTextureColorChangeComponent
{
public:
	CTextureColorChangeComponent();
	~CTextureColorChangeComponent() = default;

	float ColorChange();

private:
	int m_nTime; // �J�E���g
	float m_fColor;	// �F

};