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
SamplerState::SamplerState()
{
	m_pState = nullptr;
}

//=============================================================================
// 
// �f�X�g���N�^
// 
//=============================================================================
SamplerState::~SamplerState()
{
	SAFE_RELEASE(m_pState);
}

//=============================================================================
// 
//	����
// 
//=============================================================================
HRESULT SamplerState::Create(D3D11_FILTER filter, D3D11_TEXTURE_ADDRESS_MODE address)
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
void SamplerState::Bind()
{
	GetDeviceContext()->PSSetSamplers(0, 1, &m_pState);
	Singleton<Graphics>::GetInstance().SetSamplerState(this);
}