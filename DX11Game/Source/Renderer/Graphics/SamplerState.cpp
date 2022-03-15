//=============================================================================
// SamplerState.cpp
//=============================================================================
// Author  ���� ���V
//=============================================================================

#include "SamplerState.h"
#include "Graphics.h"

//=============================================================================
// 
// �R���X�g���N�^
// 
//=============================================================================
CSamplerState::CSamplerState()
{
	m_pState = nullptr;
}

//=============================================================================
// 
// �f�X�g���N�^
// 
//=============================================================================
CSamplerState::~CSamplerState()
{
	SAFE_RELEASE(m_pState);
}

//=============================================================================
// 
//	����
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
// �V�F�[�_�Z�b�g
// 
//=============================================================================
void CSamplerState::Bind()
{
	GetDeviceContext()->PSSetSamplers(0, 1, &m_pState);
	CSingleton<CGraphics>::GetInstance().SetSamplerState(this);
}