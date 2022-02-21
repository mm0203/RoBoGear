//=============================================================================
// CTextureColorChangeComponent.h
//=============================================================================
// Author  松野 将之
//=============================================================================
#pragma once

//=============================================================================
// 
// クラス定義
// 
//=============================================================================
class CTextureColorChangeComponent
{
public:
	CTextureColorChangeComponent();
	~CTextureColorChangeComponent() = default;

	float ColorChange(int speed = 3);

private:
	int m_nTime;	// カウント
	float m_fColor;	// 色

};