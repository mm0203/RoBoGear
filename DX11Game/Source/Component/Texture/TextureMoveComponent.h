//=============================================================================
// CTextureMoveComponent.h
//=============================================================================
// Author  松野 将之
//=============================================================================
#pragma once

#include <Renderer/Polygon/CPolygon.h>

//=============================================================================
// 
// クラス定義
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
	// カウント
	int m_nTime;
	// テクスチャ移動量
	float m_TextMove;
};