//=============================================================================
// TextureFactory.h
//=============================================================================
// Author  èºñÏ è´îV
//=============================================================================
#pragma once

#include "Texture.h"

//=============================================================================
// 
// ÉNÉâÉXíËã`
// 
//=============================================================================
class CTextureFactory
{
public:
	static Texture* CreateFromFile(const char* fileName);
	static Texture* CreateFromData(DXGI_FORMAT format, UINT width, UINT height, const void* pData);
	static Texture* CreateRenderTarget(DXGI_FORMAT format, UINT width, UINT height);
	static Texture* CreateRenderTargetFromScreen();
	static Texture* CreateDepthStencil(UINT width, UINT height, bool useStencil = false);
};