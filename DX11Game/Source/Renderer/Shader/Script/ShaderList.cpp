//=============================================================================
// ShaderList.h
//=============================================================================
// Author  ���� ���V
//=============================================================================

#include "ShaderList.h"
#include <main.h>

// �g�p���钸�_�V�F�[�_��o�^
const char* VertexShaderFile[MAX_VERTEX_SHADER] =
{
	"data/shader/Vertex2D.cso",
	"data/shader/AssimpVertex.cso",
	"data/shader/Vertex.cso",
	"data/shader/ToonOutlineVS.cso",
};

// �g�p����s�N�Z���V�F�[�_��o�^
const char* PixelShaderFile[MAX_PIXEL_SHADER] =
{
	"data/shader/Pixel2D.cso",
	"data/shader/AssimpPixel.cso",
	"data/shader/Pixel.cso",
	"data/shader/ToonOutlinePS.cso",
};

Shader* g_pVertexShaderList[MAX_VERTEX_SHADER];
Shader* g_pPixelShaderList[MAX_PIXEL_SHADER];

//=============================================================================
// 
// ���_/�s�N�Z���V�F�[�_����
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
// ���_/�s�N�Z���V�F�[�_���
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
// ���_�V�F�[�_�擾
// 
//=============================================================================
Shader* GetVertexShader(VertexShaderKind vs)
{
	return g_pVertexShaderList[vs];
}

//=============================================================================
// 
// �s�N�Z���V�F�[�_�擾
// 
//=============================================================================
Shader* GetPixelShader(PixelShaderKind ps)
{
	return g_pPixelShaderList[ps];
}