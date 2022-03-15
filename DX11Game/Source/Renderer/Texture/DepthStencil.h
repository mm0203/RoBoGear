//=============================================================================
// DepthStencil.h
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
class CDepthStencil : public Texture
{
public:
	friend class CTextureFactory; // フレンドクラス
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
