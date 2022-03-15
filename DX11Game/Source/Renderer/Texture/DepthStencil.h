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
class CDepthStencil : public Texture
{
public:
	friend class CTextureFactory; // �t�����h�N���X
public:
	CDepthStencil();
	~CDepthStencil();
	virtual void Release();

	ID3D11DepthStencilView* GetView() const;

protected:
	virtual HRESULT CreateResource(D3D11_TEXTURE2D_DESC& desc, const void* pData = nullptr);

private:
	ID3D11DepthStencilView* m_pDSV;
};
