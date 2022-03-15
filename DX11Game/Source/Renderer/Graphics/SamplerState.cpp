//=============================================================================
// SamplerState.cpp
//=============================================================================
// Author  松野 将之
//=============================================================================

#include "SamplerState.h"
#include "Graphics.h"

//=============================================================================
// 
// コンストラクタ
// 
//=============================================================================
CSamplerState::CSamplerState()
{
	m_pState = nullptr;
}

//=============================================================================
// 
// デストラクタ
// 
//=============================================================================
CSamplerState::~CSamplerState()
{
	SAFE_RELEASE(m_pState);
}

//=============================================================================
// 
//	生成
// 
//=============================================================================
HRESULT CSamplerState::Create(D3D11_FILTER filter, D3D11_TEXTURE_ADDRESS_MODE address)
{
	D3D11_SAMPLER_DESC desc = {};
	desc.Filter = filter;
	desc.AddressU = address;
	desc.AddressV = address;
	desc.AddressW = address;
	return GetDevice()->CreateSamplerState(&desc, &m_pState);
}

//=============================================================================
// 
// シェーダセット
// 
//=============================================================================
void CSamplerState::Bind()
{
	GetDeviceContext()->PSSetSamplers(0, 1, &m_pState);
	CSingleton<CGraphics>::GetInstance().SetSamplerState(this);
}