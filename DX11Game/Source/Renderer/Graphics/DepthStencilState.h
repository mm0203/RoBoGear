//=============================================================================
// DepthStencilState.h
//=============================================================================
// Author  ���� ���V
//=============================================================================
#pragma once

#include <main.h>

//=============================================================================
// 
// �N���X��`
// 
//=============================================================================
class DepthStencilState
{
public:
	DepthStencilState();
	~DepthStencilState();

	HRESULT Create(bool depthEnable, bool stencilEnable);
	void Bind();

private:
	ID3D11DepthStencilState* m_pState;
};

