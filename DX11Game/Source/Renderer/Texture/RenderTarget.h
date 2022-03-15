//=============================================================================
// RenderTarget.h
//=============================================================================
// Author  松野 将之
//=============================================================================
#pragma once

#include "Texture.h"

//=============================================================================
// 
// クラス定義
// 
//=============================================================================
class CRenderTarget : public Texture
{
public:
	friend class CTextureFactory; // フレンドクラス
public:
	CRenderTarget();
	~CRenderTarget();
	virtual void Release();

	ID3D11RenderTargetView* GetView() const;

protected:
	virtual HRESULT CreateResource(D3D11_TEXTURE2D_DESC& desc, const void* pData = nullptr);

private:
	ID3D11RenderTargetView* m_pRTV;
};