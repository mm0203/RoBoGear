//=============================================================================
// meshfield.cpp
//=============================================================================
// Author  松野 将之
//=============================================================================

#include "StageGround.h"
#include <Manager/SceneManager.h>

//=============================================================================
// 
// 定義
// 
//=============================================================================
#define SIZE_BROCK	(100.0f)
#define	TEXTURE_FILENAME	L"data/texture/field001.jpg"
#define	TEXTURE_NROMAL		L"data/texture/Bump.jpg"
#define	TEXTURE_AMBIENT		L"data/texture/Anbient001.jpg"

//=============================================================================
// 
// 無名名前空間
// 
//=============================================================================
namespace
{
	constexpr int sizeX = 21;
	constexpr int sizeY = 15;
}
//=============================================================================
// 
// コンストラクタ
// 
//=============================================================================
CStageGround::CStageGround()
{
}

//=============================================================================
// 
// 初期化処理
// 
//=============================================================================
void CStageGround::Init()
{
	ID3D11Device* pDevice = GetDevice();
	HRESULT hr;

	// テクスチャ マトリックス初期化
	XMStoreFloat4x4(&m_MeshField.m_MtxTexture, XMMatrixIdentity());

	// 位置、向きの初期設定
	m_MeshField.m_Pos = XMFLOAT3(0.0f, -1.0f, 0.0f);
	m_MeshField.m_Rot = XMFLOAT3(0.0f, 0.0f, 0.0f);

	int SceneNo = Singleton<SceneManager>::GetInstance().GetSceneNo();

	// テクスチャの読み込み
	// ステージテクスチャ
	hr = CreateTextureFromFile(pDevice,TEXTURE_FILENAME,&m_MeshField.m_pTexture);

	// エディットモードはなし
	if (SceneNo != Scene_Edit)
	{
		// バンプマップ
		hr = CreateTextureFromFile(pDevice, TEXTURE_NROMAL, &m_MeshField.m_pNormalTexture);

		// 環境マップ

		hr = CreateTextureFromFile(pDevice, TEXTURE_AMBIENT, &m_MeshField.m_pAmbientTexture);
	}

	// 頂点数の設定
	m_MeshField.m_nNumVertex = (sizeX + 1) * (sizeY + 1);

	// インデックス数の設定
	m_MeshField.m_nNumIndex = (sizeX + 1) * 2 * sizeY + (sizeY - 1) * 2;

	// ポリゴン数の設定
	int nNumPolygon = sizeX * sizeY * 2 + (sizeY - 1) * 4;

	// オブジェクトの頂点バッファを生成
	VERTEX_3D* pVertexWk = new VERTEX_3D[m_MeshField.m_nNumVertex];

	// オブジェクトのインデックスバッファを生成
	int* pIndexWk = new int[m_MeshField.m_nNumIndex];

	// 頂点バッファの中身を埋める
	VERTEX_3D* pVtx = pVertexWk;
#if 0
	const float texSizeX = 1.0f / STAGE_SIZE;
	const float texSizeZ = 1.0f / STAGE_SIZE;
#else
	const float texSizeX = 1.0f;
	const float texSizeZ = 1.0f;
#endif

	for (int nCntVtxZ = 0; nCntVtxZ < sizeY + 1; ++nCntVtxZ)
	{
		const float ANGLE = XM_2PI / sizeX;

		for (int nCntVtxX = 0; nCntVtxX < sizeX + 1; ++nCntVtxX)
		{
			// 頂点座標の設定
			pVtx[nCntVtxZ * (sizeX + 1) + nCntVtxX].vtx.x = -(sizeX / 2.0f) * SIZE_BROCK + nCntVtxX * SIZE_BROCK;
			pVtx[nCntVtxZ * (sizeX + 1) + nCntVtxX].vtx.y = 0.0f;
			pVtx[nCntVtxZ * (sizeX + 1) + nCntVtxX].vtx.z = (sizeY / 2.0f) * SIZE_BROCK - nCntVtxZ * SIZE_BROCK;

			// 法線の設定
			pVtx[nCntVtxZ * (sizeX + 1) + nCntVtxX].nor = XMFLOAT3(0.0f, 1.0, 0.0f);

			// 反射光の設定
			pVtx[nCntVtxZ * (sizeX + 1) + nCntVtxX].diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

			// テクスチャ座標の設定
			pVtx[nCntVtxZ * (sizeX + 1) + nCntVtxX].tex.x = texSizeX * nCntVtxX;
			pVtx[nCntVtxZ * (sizeX + 1) + nCntVtxX].tex.y = texSizeZ * nCntVtxZ;
		}
	}

	// インデックスバッファの中身を埋める
	int* pIdx = pIndexWk;

	int nCntIdx = 0;
	for (int nCntVtxZ = 0; nCntVtxZ < sizeY; ++nCntVtxZ)
	{
		if (nCntVtxZ > 0) 
		{
			// 縮退ポリゴンのためのダブりの設定
			pIdx[nCntIdx] = (nCntVtxZ + 1) * (sizeX + 1);
			++nCntIdx;
		}

		for (int nCntVtxX = 0; nCntVtxX < sizeX + 1; ++nCntVtxX)
		{
			pIdx[nCntIdx] = (nCntVtxZ + 1) * (sizeX + 1) + nCntVtxX;
			++nCntIdx;
			pIdx[nCntIdx] = nCntVtxZ * (sizeX + 1) + nCntVtxX;
			++nCntIdx;
		}

		if (nCntVtxZ < sizeY - 1)
		{
			// 縮退ポリゴンのためのダブりの設定
			pIdx[nCntIdx] = nCntVtxZ * (sizeX + 1) + sizeX;
			++nCntIdx;
		}
	}

	// 頂点バッファ/インデックス バッファ生成
	hr = m_MeshField.MakeMeshVertex(pDevice, &m_MeshField, pVertexWk, pIndexWk);

	// 一時配列解放
	delete[] pIndexWk;
	delete[] pVertexWk;
}

//=============================================================================
// 
// 終了処理
// 
//=============================================================================
void CStageGround::Uninit()
{
	m_MeshField.Release(&m_MeshField);
}

//=============================================================================
// 
// 更新処理
// 
//=============================================================================
void CStageGround::Update()
{
	m_MeshField.Update(&m_MeshField);
}

//=============================================================================
// 
// 描画処理
// 
//=============================================================================
void CStageGround::Draw()
{
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();

	//DrawMeshShadow(pDeviceContext, &m_MeshField);
	m_MeshField.Draw(pDeviceContext, &m_MeshField);
}
