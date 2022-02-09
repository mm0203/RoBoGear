//=============================================================================
// DepthStencil.h
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
class DepthStencil : public Texture
{
public:
	friend class TextureFactory;
public:
	DepthStencil();
	~DepthStencil();
	virtual void Release();

	ID3D11DepthStencilView* GetView() const;

protected:
	virtual HRESULT CreateResource(D3D11_TEXTURE2D_DESC& desc, const void* pData = nullptr);

private:
	ID3D11DepthStencilView* m_pDSV;
};
