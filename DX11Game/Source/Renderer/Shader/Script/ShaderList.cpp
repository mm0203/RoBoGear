//=============================================================================
// ShaderList.h
//=============================================================================
// Author  松野 将之
//=============================================================================

#include "ShaderList.h"
#include <main.h>

// 使用する頂点シェーダを登録
const char* VertexShaderFile[MAX_VERTEX_SHADER] =
{

	"data/shader/AssimpVertex.cso",
	"data/shader/Vertex.cso",
	"data/shader/ToonOutlineVS.cso",
};

// 使用するピクセルシェーダを登録
const char* PixelShaderFile[MAX_PIXEL_SHADER] =
{
	"data/shader/AssimpPixel.cso",
	"data/shader/Pixel.cso",
	"data/shader/ToonOutlinePS.cso",
};

Shader* g_pVertexShaderList[MAX_VERTEX_SHADER];
Shader* g_pPixelShaderList[MAX_PIXEL_SHADER];

//=============================================================================
// 
// 頂点/ピクセルシェーダ生成
// 
//=============================================================================
HRESULT InitShaderResource()
{
	HRESULT hr = S_OK;
	for (int i = 0; i < MAX_VERTEX_SHADER; ++i)
	{
		g_pVertexShaderList[i] = new VertexShader;
		hr = g_pVertexShaderList[i]->Load(VertexShaderFile[i]);
		if (FAILED(hr)) { return hr; }
	}
	for (int i = 0; i < MAX_PIXEL_SHADER; ++i)
	{
		g_pPixelShaderList[i] = new PixelShader;
		hr = g_pPixelShaderList[i]->Load(PixelShaderFile[i]);
		if (FAILED(hr)) { return hr; }
	}
	return hr;
}
//=============================================================================
// 
// 頂点/ピクセルシェーダ解放
// 
//=============================================================================
void UninitShaderResource()
{
	for (int i = 0; i < MAX_PIXEL_SHADER; ++i)
	{
		SAFE_DELETE(g_pPixelShaderList[i]);
	}
	for (int i = 0; i < MAX_VERTEX_SHADER; ++i)
	{
		SAFE_DELETE(g_pVertexShaderList[i]);
	}
}
//=============================================================================
// 
// 頂点シェーダ取得
// 
//=============================================================================
Shader* GetVertexShader(VertexShaderKind vs)
{
	return g_pVertexShaderList[vs];
}

//=============================================================================
// 
// ピクセルシェーダ取得
// 
//=============================================================================
Shader* GetPixelShader(PixelShaderKind ps)
{
	return g_pPixelShaderList[ps];
}