//=============================================================================
// DepthStencilState.h
//=============================================================================
// Author  èºñÏ è´îV
//=============================================================================
#pragma once

#include <main.h>

//=============================================================================
// 
// ÉNÉâÉXíËã`
// 
//=============================================================================
class CDepthStencilState
{
public:
	CDepthStencilState();
	~CDepthStencilState();

	HRESULT Create(bool depthEnable, bool stencilEnable);
	void Bind();

private:
	ID3D11DepthStencilState* m_pState;
};

