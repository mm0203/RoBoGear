//=============================================================================
// DepthStencil.cpp
//=============================================================================
// Author  ���� ���V
//=============================================================================

#include "DepthStencil.h"
#include <main.h>

//=============================================================================
// 
// �R���X�g���N�^
// 
//=============================================================================
CDepthStencil::CDepthStencil()
{
	m_pDSV = nullptr;
}

//=============================================================================
// 
// �f�X�g���N�^
// 
//=============================================================================
CDepthStencil::~CDepthStencil()
{
}

//=============================================================================
// 
// ���
// 
//=============================================================================
void CDepthStencil::Release()
{
	Texture::Release();
	SAFE_RELEASE(m_pDSV);
}

//=============================================================================
// 
// �[�x�l�擾
// 
//=============================================================================
ID3D11DepthStencilView* CDepthStencil::GetView() const
{
	return m_pDSV;
}
//=============================================================================
// 
// ����
// 
//=============================================================================
HRESULT CDepthStencil::CreateResource(D3D11_TEXTURE2D_DESC& desc, const void* pData)
{
	// �X�e���V���g�p����
	bool useStencil = (desc.Format == DXGI_FORMAT_D24_UNORM_S8_UINT);

	// ���\�[�X����
	desc.Format = useStencil ? DXGI_FORMAT_R24_UNORM_X8_TYPELESS : DXGI_FORMAT_R32_TYPELESS;
	HRESULT hr = Texture::CreateResource(desc, nullptr);

	// �ݒ�
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = useStencil ? DXGI_FORMAT_D24_UNORM_S8_UINT : DXGI_FORMAT_D32_FLOAT;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

	// ����
	return GetDevice()->CreateDepthStencilView(m_pTex, &dsvDesc, &m_pDSV);
}