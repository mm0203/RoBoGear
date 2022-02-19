//=============================================================================
// ShaderList.h
//=============================================================================
// Author  松野 将之
//=============================================================================

#pragma once
#include "Shader.h"

//=============================================================================
// 
// マクロ定義
// 
//=============================================================================

// 頂点シェーダ
enum VertexShaderKind
{
	POLYGON_VS,
	ASSIMP_VS,
	MESH_VS,
	TOON_OUTLINE_VS,
	MAX_VERTEX_SHADER
};

// ピクセルシェーダ
enum PixelShaderKind
{
	POLYGON_PS,
	ASSIMP_PS,
	MESH_PS,
	TOON_OUTLINE_PS,
	MAX_PIXEL_SHADER
};
//=============================================================================
// 
// プロトタイプ宣言
// 
//=============================================================================
HRESULT InitShaderResource();
void UninitShaderResource();
Shader* GetVertexShader(VertexShaderKind vs);
Shader* GetPixelShader(PixelShaderKind ps);
