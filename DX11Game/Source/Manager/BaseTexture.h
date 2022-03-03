//=============================================================================
// BaseTexture.h
//=============================================================================
// Author  松野 将之
//=============================================================================
#pragma once

#include <Renderer/Polygon/CPolygon.h>
#include <Component/Texture/TextureFadeComponent.h>
#include <Component/Texture/TextureMoveComponent.h>
#include <Component/Texture/TextureColorChangeComponent.h>
#include <memory>

//=============================================================================
// 
// クラス定義
// 
//=============================================================================
// 前方宣言
class CBaseTexture;

// 型定義
typedef std::shared_ptr<CBaseTexture> tex_shared;

class CBaseTexture
{
public:
	CBaseTexture();
	virtual ~CBaseTexture() = default;

	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

protected:
	// ポリゴン描画用変数
	std::shared_ptr<CPolygon> m_Polygon;
	// フェードオブジェクト
	std::shared_ptr<CTextureFadeComponent> m_TextureFade;
	// 移動オブジェクト
	std::shared_ptr<CTextureMoveComponent> m_TextureMove;
	// 色変更オブジェクト
	std::shared_ptr<CTextureColorChangeComponent> m_TextureColor;
};