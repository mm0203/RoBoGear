//=============================================================================
// CMesh.h
//=============================================================================
// Author  松野 将之
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
// 定数
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
	TT_NOAFFECT = 0,	// 全て
	TT_OPACITYONLY,		// 不透明のみ
	TT_TRANSLUCENTONLY,	// 半透明のみ

	MAX_TRANSLUCENTTYPE
};

//=============================================================================
// 
// 定数
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
// クラス定義
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
	XMFLOAT3 m_Pos;		// ポリゴン表示位置の中心座標
	XMFLOAT3 m_Rot;		// ポリゴンの回転角
	int m_nNumVertex;	// 総頂点数	
	int m_nNumIndex;	// 総インデックス数
	float m_fAlpha;
	bool m_bLight;

	XMFLOAT4X4 m_MtxTexture;	// テクスチャマトリックス
	ID3D11ShaderResourceView* m_pTexture;		 // テクスチャ
	ID3D11ShaderResourceView* m_pNormalTexture;	 // 法線テクスチャ
	ID3D11ShaderResourceView* m_pAmbientTexture; // 環境テクスチャ

	ePrimitiveType m_PrimitiveType;	 // プリミティブ型
	MATERIAL* m_pMaterial;	 // マテリアル
	DXBuffer* m_pMeshBuffer; // 頂点&インデックスバッファ

	static MATERIAL	m_Material;		// マテリアル
	static ConstantBuffer* m_pWorldBuffer;
	static ConstantBuffer* m_pLightBuffer;
	//static SamplerState* m_pShadowSamplerState;
	//static Texture* m_pShadowDepthStencil;
private:
};
