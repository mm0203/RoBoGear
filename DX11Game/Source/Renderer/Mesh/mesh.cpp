//=============================================================================
// CMesh.cpp
//=============================================================================
// Author  松野 将之
//=============================================================================
#include "mesh.h"

#include <Manager/GameManager.h>

// レンダー
#include <Renderer/Graphics/Graphics.h>
#include <Renderer/Shader/Script/Shader.h>
#include <Renderer/Shader/Script/ShaderList.h>

// システム
#include <System/Singleton/singleton.h>
#include <System/Camera/Camera.h>
#include <System/Light/Light.h>
#include <System/Input/input.h>

//=============================================================================
// 
// 無名名前空間
// 
//=============================================================================
namespace
{
	constexpr XMFLOAT4 MaterialDiffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	constexpr XMFLOAT4 MaterialSpecular = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);
	constexpr XMFLOAT4 MaterialAmbient  = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	constexpr XMFLOAT4 MaterialEmissive = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
}

//=============================================================================
// 
// 静的メンバ
// 
//=============================================================================
ConstantBuffer* CMesh::m_pWorldBuffer;
ConstantBuffer* CMesh::m_pLightBuffer;
MATERIAL CMesh::m_Material;

//SamplerState* CMesh::m_pShadowSamplerState = nullptr;
//Texture* CMesh::m_pShadowDepthStencil = nullptr;

//=============================================================================
// 
// 構造体定義
// 
//=============================================================================
struct SHADER_GLOBAL
{
	XMMATRIX	mWVP;		// ワールド×ビュー×射影行列(転置行列)
	XMMATRIX	mLightWVP;	// ワールド×ビュー×射影行列(転置行列)
	XMMATRIX	mW;			// ワールド行列(転置行列)
	XMMATRIX	mTex;		// テクスチャ行列(転置行列)
	XMVECTOR	vFog;		// フォグ係数
};
struct SHADER_GLOBAL2
{
	XMVECTOR	vEye;		// 視点座標
	// 光源
	XMVECTOR	vLightDir;	// 光源方向
	XMVECTOR	vLa;		// 光源色(アンビエント)
	XMVECTOR	vLd;		// 光源色(ディフューズ)
	XMVECTOR	vLs;		// 光源色(スペキュラ)
	// マテリアル
	XMVECTOR	vAmbient;	// アンビエント色(+テクスチャ有無)
	XMVECTOR	vDiffuse;	// ディフューズ色
	XMVECTOR	vSpecular;	// スペキュラ色(+スペキュラ強度)
	XMVECTOR	vEmissive;	// エミッシブ色

	int		bLight = true;
	int		bBump = false;
	int		bAnbient = false;
};

//=============================================================================
// 
// グローバル変数
// 
//=============================================================================
CMesh::CMesh()
{
	m_MtxWorld = XMFLOAT4X4();
 	m_Pos = XMFLOAT3();
 	m_Rot = XMFLOAT3();
	m_nNumVertex = 0;
	m_nNumIndex = 0;
	m_fAlpha = 0.0f;
	m_bLight = true;
	m_MtxTexture = XMFLOAT4X4();
	m_pTexture = nullptr;
	m_pNormalTexture = nullptr;
	m_pAmbientTexture = nullptr;
	m_PrimitiveType = PT_UNDEFINED;
	m_pMaterial = nullptr;
	m_pMeshBuffer = nullptr;
}
//=============================================================================
// 
// 初期化処理
// 
//=============================================================================
void CMesh::Init()
{
	// 定数バッファ生成
	m_pWorldBuffer = new ConstantBuffer;
	m_pWorldBuffer->Create(sizeof(SHADER_GLOBAL));
	m_pLightBuffer = new ConstantBuffer;
	m_pLightBuffer->Create(sizeof(SHADER_GLOBAL2));

	// マテリアル初期設定
	m_Material.Diffuse = MaterialDiffuse;
	m_Material.Specular = MaterialSpecular;
	m_Material.Ambient = MaterialAmbient;
	m_Material.Emissive = MaterialEmissive;
	m_Material.Power = 0.0f;

	// シャドウマップステンシル
	//m_pShadowDepthStencil = TextureFactory::CreateDepthStencil(static_cast<UINT>(SCREEN_WIDTH), static_cast<UINT>(SCREEN_HEIGHT));
	//// シャドウマップサンプラ
	//m_pShadowSamplerState->Create(D3D11_FILTER_MIN_MAG_MIP_LINEAR, D3D11_TEXTURE_ADDRESS_WRAP);
}

//=============================================================================
// 
// 終了処理
// 
//=============================================================================
void CMesh::Uninit()
{
	SAFE_DELETE(m_pWorldBuffer);
	SAFE_DELETE(m_pLightBuffer);
}

//=============================================================================
// 
// 更新処理
// 
//=============================================================================
void CMesh::Update(CMesh* pMesh)
{
	XMMATRIX m_MtxWorld, mtxRot, mtxTranslate;

	if (!pMesh) return;
	m_MtxWorld = XMMatrixIdentity();

	// 回転
	mtxRot = XMMatrixRotationRollPitchYaw(XMConvertToRadians(pMesh->m_Rot.x), XMConvertToRadians(pMesh->m_Rot.y), XMConvertToRadians(pMesh->m_Rot.z));
	m_MtxWorld = XMMatrixMultiply(m_MtxWorld, mtxRot);
	// 移動
	mtxTranslate = XMMatrixTranslation(pMesh->m_Pos.x, pMesh->m_Pos.y, pMesh->m_Pos.z);
	m_MtxWorld = XMMatrixMultiply(m_MtxWorld, mtxTranslate);

	DirectX::XMStoreFloat4x4(&pMesh->m_MtxWorld, m_MtxWorld);
}

//=============================================================================
// 
// 描画処理
// 
//=============================================================================
void CMesh::Draw(ID3D11DeviceContext* pDeviceContext, CMesh* pMesh, int nTranslucntType)
{
	MATERIAL* pMaterial = pMesh->m_pMaterial;
	if (!pMaterial) pMaterial = &m_Material;
	switch (nTranslucntType)
	{
	case TT_OPACITYONLY: // 不透明のみ
		if (pMaterial->Diffuse.w < 1.0f || pMesh->m_fAlpha < 1.0f)
			return;
		break;
	case TT_TRANSLUCENTONLY: // 半透明のみ
		if (pMaterial->Diffuse.w >= 1.0f && pMesh->m_fAlpha >= 1.0f)
			return;
		break;
	default: // 不透明度で区別しない
		break;
	}

	// シェーダセット
	GetVertexShader(MESH_VS)->Bind();
	GetPixelShader(MESH_PS)->Bind();

	// テクスチャ
	ID3D11ShaderResourceView* pResource[3] = { pMesh->m_pTexture, pMesh->m_pNormalTexture, pMesh->m_pAmbientTexture };
	// サンプラセット
	Singleton<Graphics>::GetInstance().SetSamplerState(SAMPLER_LINEAR);
	// テクスチャセット
	pDeviceContext->PSSetShaderResources(0, 3, pResource);

	SHADER_GLOBAL cb;
	XMMATRIX m_MtxWorld = DirectX::XMLoadFloat4x4(&pMesh->m_MtxWorld);
	CCamera& pCamera = Singleton<CCamera>::GetInstance();
	CLight* pLight = &Singleton<CLight>::GetInstance();

	//XMMATRIX SHADOW_BIAS = XMMATRIX(
	//	0.5f, 0.0f, 0.0f, 0.0f,
	//	0.0f, -0.5f, 0.0f, 0.0f,
	//	0.0f, 0.0f, 1.0f, 0.0f,
	//	0.5f, 0.5f, 0.0f, 1.0f);

	cb.mWVP = XMMatrixTranspose(m_MtxWorld * DirectX::XMLoadFloat4x4(&pCamera.GetViewMatrix()) * DirectX::XMLoadFloat4x4(&pCamera.GetProjMatrix()));
	cb.mLightWVP = XMMatrixTranspose(m_MtxWorld * DirectX::XMLoadFloat4x4(&pLight->GetViewMatrix()) * DirectX::XMLoadFloat4x4(&pCamera.GetProjMatrix())/*SHADOW_BIAS*/);
	cb.mW = XMMatrixTranspose(m_MtxWorld);
	cb.mTex = XMMatrixTranspose(DirectX::XMLoadFloat4x4(&pMesh->m_MtxTexture));
	XMFLOAT2 fog = { FOG_FAR_Z / (FOG_FAR_Z - FOG_NEAR_Z), -1 / (FOG_FAR_Z - FOG_NEAR_Z) };
	cb.vFog = XMLoadFloat2(&fog);

	m_pWorldBuffer->Write(&cb);
	m_pWorldBuffer->BindVS(0);

	SHADER_GLOBAL2 cb2;
	cb2.vEye = DirectX::XMLoadFloat3(&pCamera.GetPos());
	cb2.vLightDir = DirectX::XMLoadFloat3(&pLight->GetDir());
	cb2.vLa = DirectX::XMLoadFloat4(&pLight->GetAmbient());
	cb2.vLd = DirectX::XMLoadFloat4(&pLight->GetDiffuse());
	cb2.vLs = DirectX::XMLoadFloat4(&pLight->GetSpecular());
	cb2.vDiffuse = DirectX::XMLoadFloat4(&pMaterial->Diffuse);
	cb2.vAmbient = XMVectorSet(pMaterial->Ambient.x, pMaterial->Ambient.y, pMaterial->Ambient.z, (pMesh->m_pTexture != nullptr) ? 1.f : 0.f);
	cb2.vSpecular = XMVectorSet(pMaterial->Specular.x, pMaterial->Specular.y, pMaterial->Specular.z, pMaterial->Power);
	cb2.vEmissive = DirectX::XMLoadFloat4(&pMaterial->Emissive);

	// バンプマップ表示
	bool bump = false;
	// バンプマップ表示切り替え
	if (pMesh->m_pNormalTexture)
		bump = true;
	if (CGameManager::GetDebug() && GetKeyPress(VK_C))
		bump = false;
	cb2.bBump = bump;
	
	// 環境マップ表示
	bool anbient = false;
	// 環境マップ表示切り替え
	if (pMesh->m_pAmbientTexture) 
		anbient = true;
	if (CGameManager::GetDebug() && GetKeyPress(VK_V))
		anbient = false;
	cb2.bAnbient = anbient;


	cb2.bLight = pMesh->m_bLight;

	m_pLightBuffer->Write(&cb2);
	m_pLightBuffer->BindPS(1);
	
	// メッシュ描画
	pMesh->m_pMeshBuffer->Draw(pMesh->m_nNumIndex);
}

//=============================================================================
// 
// 頂点の作成
// 
//=============================================================================
HRESULT CMesh::MakeMeshVertex(ID3D11Device* pDevice, CMesh* pMesh, VERTEX_3D vertexWk[], int indexWk[])
{
	HRESULT hr = S_OK;

	pMesh->m_fAlpha = 1.0f;
	for (int i = 0; i < pMesh->m_nNumVertex; ++i)
	{
		if (pMesh->m_fAlpha > vertexWk[i].diffuse.w)
			pMesh->m_fAlpha = vertexWk[i].diffuse.w;
	}

	// 頂点&インデックスバッファ 生成
	DXBuffer::Desc desc;
	desc.vtxSize = sizeof(VERTEX_3D);
	desc.vtxCount = pMesh->m_nNumVertex;
	desc.idxSize = sizeof(int);
	desc.idxCount = pMesh->m_nNumIndex;
	desc.isWrite = true;
	desc.pVtx = &vertexWk[0];
	desc.pIdx = &indexWk[0];

	// プリミティブ形状をセット
	static const D3D11_PRIMITIVE_TOPOLOGY pt[] =
	{
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,	// 0なら三角形ストリップ
		D3D11_PRIMITIVE_TOPOLOGY_POINTLIST,
		D3D11_PRIMITIVE_TOPOLOGY_LINELIST,
		D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP,
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,
	};
	desc.topology = pt[pMesh->m_PrimitiveType];
	pMesh->m_pMeshBuffer = new DXBuffer();
	hr = pMesh->m_pMeshBuffer->Create(desc);
	if (FAILED(hr)) { return hr; }

	return hr;
}

//=============================================================================
// 
// メッシュ解放
// 
//=============================================================================
void CMesh::Release(CMesh* pMesh)
{
	if (!pMesh) return;
	SAFE_RELEASE(pMesh->m_pTexture);
	SAFE_RELEASE(pMesh->m_pNormalTexture);
	SAFE_RELEASE(pMesh->m_pAmbientTexture);
	SAFE_DELETE(pMesh->m_pMeshBuffer);
	SAFE_DELETE(pMesh->m_pMaterial);
}