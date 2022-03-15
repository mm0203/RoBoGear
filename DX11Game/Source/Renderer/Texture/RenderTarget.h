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
class CRenderTarget : public Texture
{
public:
	friend class CTextureFactory; // �t�����h�N���X
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