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
	// マップの最大サイズ
	const int sizeX = 21;
	const int sizeY = 15;
}
//=============================================================================
// 
// コンストラクタ
// 
//=============================================================================
CStageGround::CStageGround()
{
	m_tag = TagStageGround;
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
	XMFLOAT4X4& MtxTexture = m_MeshField.GetMtxTexture();
	XMStoreFloat4x4(&MtxTexture, XMMatrixIdentity());

	// 位置、向きの初期設定
	XMFLOAT3& pos = m_MeshField.GetPos();
	XMFLOAT3& rot = m_MeshField.GetRot();
	pos = XMFLOAT3(0.0f, -1.0f, 0.0f);
	rot = XMFLOAT3(0.0f, 0.0f, 0.0f);

	int SceneNo = CSingleton<CSceneManager>::GetInstance().GetSceneNo();

	// テクスチャ読み込み
	ID3D11ShaderResourceView* pTexture;

	// フィールド用テクスチャ
	hr = CreateTextureFromFile(pDevice,TEXTURE_FILENAME,&pTexture);
	m_MeshField.SetTexture(pTexture);

	// エディットモードは表示しない
	if (SceneNo != eSceneEdit)
	{
		// バンプマップ
		hr = CreateTextureFromFile(pDevice, TEXTURE_NROMAL, &pTexture);
		m_MeshField.SetNormalTexture(pTexture);

		// 環境マップ
		hr = CreateTextureFromFile(pDevice, TEXTURE_AMBIENT, &pTexture);
		m_MeshField.SetAmbientTexture(pTexture);
	}

	// 頂点数の設定
	int& NumVertex = m_MeshField.GetNumVertex();
	NumVertex = (sizeX + 1) * (sizeY + 1);

	// インデックス数の設定
	int& NumIndex = m_MeshField.GetNumIndex();
	NumIndex = (sizeX + 1) * 2 * sizeY + (sizeY - 1) * 2;

	// ポリゴン数の設定
	int nNumPolygon = sizeX * sizeY * 2 + (sizeY - 1) * 4;

	// オブジェクトの頂点バッファを生成
	VERTEX_3D* pVertexWk = new VERTEX_3D[NumVertex];

	// オブジェクトのインデックスバッファを生成
	int* pIndexWk = new int[NumIndex];

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
