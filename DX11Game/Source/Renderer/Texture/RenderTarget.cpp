//=============================================================================
// RenderTarget.cpp
//=============================================================================
// Author  松野 将之
//=============================================================================

#include "RenderTarget.h"
#include <main.h>

//=============================================================================
// 
// コンストラクタ
// 
//=============================================================================
CRenderTarget::CRenderTarget()
{
	m_pRTV = nullptr;
}
//=============================================================================
// 
// デストラクタ
// 
//=============================================================================
CRenderTarget::~CRenderTarget()
{
}

//=============================================================================
// 
// 解放
// 
//=============================================================================
void CRenderTarget::Release()
{
	Texture::Release();
	SAFE_RELEASE(m_pRTV);
}

//=============================================================================
// 
// レンダー取得
// 
//=============================================================================
ID3D11RenderTargetView* CRenderTarget::GetView() const
{
	return m_pRTV;
}

//=============================================================================
// 
// 生成
// 
//=============================================================================
HRESULT CRenderTarget::CreateResource(D3D11_TEXTURE2D_DESC& desc, const void* pData)
{
	// テクスチャリソース作成
	HRESULT hr = Texture::CreateResource(desc, nullptr);
	if (FAILED(hr)) { return hr; }

	// 設定
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};
	rtvDesc.Format = desc.Format;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

	// 生成
	return GetDevice()->CreateRenderTargetView(m_pTex, &rtvDesc, &m_pRTV);
}