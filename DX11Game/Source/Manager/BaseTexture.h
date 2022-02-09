//=============================================================================
// BaseTexture.h
//=============================================================================
// Author  ���� ���V
//=============================================================================
#pragma once

#include <Renderer/Polygon/CPolygon.h>
#include <Component/Texture/TextureFadeComponent.h>
#include <Component/Texture/TextureMoveComponent.h>
#include <Component/Texture/TextureColorChangeComponent.h>
#include <memory>

//=============================================================================
// 
// �N���X��`
// 
//=============================================================================
// �O���錾
class CBaseTexture;

// �^��`
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
	std::shared_ptr<CPolygon> m_Polygon;
	std::shared_ptr<CTextureFadeComponent> m_TextureFade;
	std::shared_ptr<CTextureMoveComponent> m_TextureMove;
	std::shared_ptr<CTextureColorChangeComponent> m_TextureColor;
};