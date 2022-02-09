//=============================================================================
// RenderTarget.h
//=============================================================================
// Author  ���� ���V
//=============================================================================
#pragma once

#include "Texture.h"

//=============================================================================
// 
// �N���X��`
// 
//=============================================================================
class RenderTarget : public Texture
{
public:
	friend class TextureFactory;
public:
	RenderTarget();
	~RenderTarget();
	virtual void Release();

	ID3D11RenderTargetView* GetView() const;

protected:
	virtual HRESULT CreateResource(D3D11_TEXTURE2D_DESC& desc, const void* pData = nullptr);

private:
	ID3D11RenderTargetView* m_pRTV;
};