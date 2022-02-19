//=============================================================================
// ShaderList.h
//=============================================================================
// Author  ���� ���V
//=============================================================================

#pragma once
#include "Shader.h"

//=============================================================================
// 
// �}�N����`
// 
//=============================================================================

// ���_�V�F�[�_
enum VertexShaderKind
{
	POLYGON_VS,
	ASSIMP_VS,
	MESH_VS,
	TOON_OUTLINE_VS,
	MAX_VERTEX_SHADER
};

// �s�N�Z���V�F�[�_
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
// �v���g�^�C�v�錾
// 
//=============================================================================
HRESULT InitShaderResource();
void UninitShaderResource();
Shader* GetVertexShader(VertexShaderKind vs);
Shader* GetPixelShader(PixelShaderKind ps);
