//=============================================================================
// DepthStencil.cpp
//=============================================================================
// Author  松野 将之
//=============================================================================

#include "DepthStencil.h"
#include <main.h>

//=============================================================================
// 
// コンストラクタ
// 
//=============================================================================
CDepthStencil::CDepthStencil()
{
	m_pDSV = nullptr;
}

//=============================================================================
// 
// デストラクタ
// 
//=============================================================================
CDepthStencil::~CDepthStencil()
{
}

//=============================================================================
// 
// 解放
// 
//=============================================================================
void CDepthStencil::Release()
{
	Texture::Release();
	SAFE_RELEASE(m_pDSV);
}

//=============================================================================
// 
// 深度値取得
// 
//=============================================================================
ID3D11DepthStencilView* CDepthStencil::GetView() const
{
	return m_pDSV;
}
//=============================================================================
// 
// 生成
// 
//=============================================================================
HRESULT CDepthStencil::CreateResource(D3D11_TEXTURE2D_DESC& desc, const void* pData)
{
	// ステンシル使用判定
	bool useStencil = (desc.Format == DXGI_FORMAT_D24_UNORM_S8_UINT);

	// リソース生成
	desc.Format = useStencil ? DXGI_FORMAT_R24_UNORM_X8_TYPELESS : DXGI_FORMAT_R32_TYPELESS;
	HRESULT hr = Texture::CreateResource(desc, nullptr);

	// 設定
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = useStencil ? DXGI_FORMAT_D24_UNORM_S8_UINT : DXGI_FORMAT_D32_FLOAT;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

	// 生成
	return GetDevice()->CreateDepthStencilView(m_pTex, &dsvDesc, &m_pDSV);
}