//=============================================================================
// CMesh.h
//=============================================================================
// Author  ���� ���V
//=============================================================================
#pragma once

#include <main.h>
#include <Renderer/Texture/Texture.h>
#include <Renderer/Texture/TextureFactory.h>
#include <Renderer/Graphics/DXBuffer.h>
#include <Renderer/Graphics/SamplerState.h>
#include <Renderer/Shader/Script/Shader.h>

//=============================================================================
// 
// �萔
// 
//=============================================================================
enum ePrimitiveType 
{
	PT_UNDEFINED = 0,
	PT_POINT,
	PT_LINE,
	PT_LINESTRIP,
	PT_TRIANGLE,
	PT_TRIANGLESTRIP,

	MAX_PRIMITIVETYPE
};
enum eTranslucentType 
{
	TT_NOAFFECT = 0,	// �S��
	TT_OPACITYONLY,		// �s�����̂�
	TT_TRANSLUCENTONLY,	// �������̂�

	MAX_TRANSLUCENTTYPE
};

//=============================================================================
// 
// �萔
// 
//=============================================================================
struct MATERIAL
{
	XMFLOAT4	Diffuse  =	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);;
	XMFLOAT4	Ambient	 =	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);;
	XMFLOAT4	Specular =	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);;
	XMFLOAT4	Emissive =	XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);;
	float		Power	 =	50.0f;
} ;

//=============================================================================
// 
// �N���X��`
// 
//=============================================================================
class CMesh
{
public:
	CMesh();
	~CMesh() = default;

	static void Init();
	static void Uninit();
	void Update(CMesh* pMesh);
	void Draw(ID3D11DeviceContext* pDeviceContext, CMesh* pMesh, int nTranslucntType = TT_NOAFFECT);
	HRESULT MakeMeshVertex(ID3D11Device* pDevice, CMesh* pMesh, VERTEX_3D vertexWk[], int indexWk[]);
	void Release(CMesh* pMesh);

	XMFLOAT4X4 m_MtxWorld;
	XMFLOAT3 m_Pos;		// �|���S���\���ʒu�̒��S���W
	XMFLOAT3 m_Rot;		// �|���S���̉�]�p
	int m_nNumVertex;	// �����_��	
	int m_nNumIndex;	// ���C���f�b�N�X��
	float m_fAlpha;
	bool m_bLight;

	XMFLOAT4X4 m_MtxTexture;	// �e�N�X�`���}�g���b�N�X
	ID3D11ShaderResourceView* m_pTexture;		 // �e�N�X�`��
	ID3D11ShaderResourceView* m_pNormalTexture;	 // �@���e�N�X�`��
	ID3D11ShaderResourceView* m_pAmbientTexture; // ���e�N�X�`��

	ePrimitiveType m_PrimitiveType;	 // �v���~�e�B�u�^
	MATERIAL* m_pMaterial;	 // �}�e���A��
	DXBuffer* m_pMeshBuffer; // ���_&�C���f�b�N�X�o�b�t�@

	static MATERIAL	m_Material;		// �}�e���A��
	static ConstantBuffer* m_pWorldBuffer;
	static ConstantBuffer* m_pLightBuffer;
	//static SamplerState* m_pShadowSamplerState;
	//static Texture* m_pShadowDepthStencil;
private:
};
