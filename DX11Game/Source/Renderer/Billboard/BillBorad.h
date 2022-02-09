//=============================================================================
// BillBoard.h
//=============================================================================
// Author  松野 将之
//=============================================================================
#pragma once

#include <main.h>

// システム
#include <System/Singleton/singleton.h>
#include <System/Camera/Camera.h>
#include <System/Light/Light.h>

// レンダー
#include <Renderer/Mesh/mesh.h>
#include <Renderer/Texture/Texture.h>

using namespace DirectX;

//=============================================================================
// 
// クラス定義
// 
//=============================================================================
class BillBoard abstract
{
public:
	BillBoard(): m_BillMesh(){}
	~BillBoard() = default;

	// テクスチャロード
	HRESULT LoadBillTexture(const wchar_t* FileName)
	{
		HRESULT hr = S_OK;
		hr = CreateTextureFromFile(GetDevice(), FileName, &m_BillMesh.m_pTexture);
		return hr;
	}
	HRESULT LoadBillTexture(const char* FileName)
	{
		HRESULT hr = S_OK;
		hr = CreateTextureFromFile(GetDevice(), FileName, &m_BillMesh.m_pTexture);
		return hr;
	}

public:
	void InitBill()
	{
		m_BillPos = XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_BillSize = XMFLOAT2(1.0f, 1.0f);
		m_BillUV = XMFLOAT2(0.0f, 0.0f);
		m_BillFrameSize = XMFLOAT2(1.0f, 1.0f);
		m_BillAngleY = 0.0f;
		m_isBillInit = false;

		m_isBillFrameInit = false;
		m_BillFrameNum = XMINT2(1, 1);
		m_BillDiffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	}
	void UpdateBill() { m_BillMesh.Update(&m_BillMesh); }
	void DrawBill(int AnimNum = 0)
	{
		// 初期化されていなければここで初期化
		if (!m_isBillInit)
		{
			ID3D11Device* pDevice = GetDevice();
			HRESULT hr = S_OK;
			// マテリアルの初期設定
			m_BillMaterial.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			m_BillMaterial.Ambient = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
			m_BillMaterial.Specular = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
			m_BillMaterial.Power = 0.0f;
			m_BillMaterial.Emissive = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
			//m_BillMesh.m_pMaterial = &m_BillMaterial;
			m_BillMesh.m_pMaterial = nullptr;

			// テクスチャマトリックスの設定
			XMStoreFloat4x4(&m_BillMesh.m_MtxTexture, XMMatrixIdentity());

			// ワールドマトリックス初期化
			XMStoreFloat4x4(&m_BillMesh.m_MtxWorld, XMMatrixIdentity());

			// プリミティブタイプ設定
			m_BillMesh.m_PrimitiveType = PT_TRIANGLESTRIP;

			// 頂点情報の作成
			m_BillMesh.m_nNumVertex = 4;
			VERTEX_3D* pVertexWk = new VERTEX_3D[m_BillMesh.m_nNumVertex];
			pVertexWk[0].vtx = XMFLOAT3(-0.5f, 0.5f, 0.0f);
			pVertexWk[1].vtx = XMFLOAT3(0.5f, 0.5f, 0.0f);
			pVertexWk[2].vtx = XMFLOAT3(-0.5f, -0.5f, 0.0f);
			pVertexWk[3].vtx = XMFLOAT3(0.5f, -0.5f, 0.0f);
			pVertexWk[0].diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			pVertexWk[1].diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			pVertexWk[2].diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			pVertexWk[3].diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			pVertexWk[0].nor = XMFLOAT3(0.0f, 0.0f, -1.0f);
			pVertexWk[1].nor = XMFLOAT3(0.0f, 0.0f, -1.0f);
			pVertexWk[2].nor = XMFLOAT3(0.0f, 0.0f, -1.0f);
			pVertexWk[3].nor = XMFLOAT3(0.0f, 0.0f, -1.0f);
			pVertexWk[0].tex = XMFLOAT2(0.0f, 0.0f);
			pVertexWk[1].tex = XMFLOAT2(1.0f, 0.0f);
			pVertexWk[2].tex = XMFLOAT2(0.0f, 1.0f);
			pVertexWk[3].tex = XMFLOAT2(1.0f, 1.0f);
			m_BillMesh.m_nNumIndex = 4;
			int* pIndexWk = new int[4];
			pIndexWk[0] = 0;
			pIndexWk[1] = 1;
			pIndexWk[2] = 2;
			pIndexWk[3] = 3;
			hr = m_BillMesh.MakeMeshVertex(pDevice, &m_BillMesh, pVertexWk, pIndexWk);
			delete[] pIndexWk;
			delete[] pVertexWk;

			m_isBillInit = true;
		}

		// ライトオフ
		Singleton<CLight>::GetInstance().SetDisable();
		//CLight::Get()->SetDisable();

		// アルファブレンド
		SetBlendState(BS_ALPHABLEND);

		// 位置更新
		m_BillMesh.m_Pos = m_BillPos;

		// カメラビューマトリクス取得
		XMFLOAT4X4 mView = Singleton<CCamera>::GetInstance().GetViewMatrix();

		m_BillMesh.m_MtxWorld._11 = mView._11;
		m_BillMesh.m_MtxWorld._12 = mView._21;
		m_BillMesh.m_MtxWorld._13 = mView._31;
		m_BillMesh.m_MtxWorld._21 = mView._12;
		m_BillMesh.m_MtxWorld._22 = mView._22;
		m_BillMesh.m_MtxWorld._23 = mView._32;
		m_BillMesh.m_MtxWorld._31 = mView._13;
		m_BillMesh.m_MtxWorld._32 = mView._23;
		m_BillMesh.m_MtxWorld._33 = mView._33;


		// サイズ変更
		//m_BillMesh.m_MtxWorld._11 *= (m_BillSize.x * 2);
		//m_BillMesh.m_MtxWorld._22 *= (m_BillSize.y * 2);

		XMMATRIX mScale = XMMatrixScaling(m_BillSize.x * 2, m_BillSize.y * 2, 1.0f);
		XMStoreFloat4x4(&m_BillMesh.m_MtxWorld, XMMatrixMultiply(mScale, XMLoadFloat4x4(&m_BillMesh.m_MtxWorld)));
		// 位置を反映
		m_BillMesh.m_MtxWorld._41 = m_BillPos.x;
		m_BillMesh.m_MtxWorld._42 = m_BillPos.y;
		m_BillMesh.m_MtxWorld._43 = m_BillPos.z;

		// テクスチャ座標移動 
		if (m_isBillFrameInit)
		{
			XMMATRIX m_MtxTexture, mtxScale, mtxTranslate;

			int u = AnimNum % m_BillFrameNum.x;
			int v = AnimNum / m_BillFrameNum.y;

			// テクスチャマトリックスの初期化
			m_MtxTexture = XMMatrixIdentity();

			// スケールを反映
			mtxScale = XMMatrixScaling(m_BillFrameSize.x, m_BillFrameSize.y, 1.0f);
			m_MtxTexture = XMMatrixMultiply(m_MtxTexture, mtxScale);

			// 移動を反映
			mtxTranslate = XMMatrixTranslation(m_BillFrameSize.x * u, m_BillFrameSize.y * v, 0.0f);
			m_MtxTexture = XMMatrixMultiply(m_MtxTexture, mtxTranslate);

			// テクスチャマトリックスの設定
			XMStoreFloat4x4(&m_BillMesh.m_MtxTexture, m_MtxTexture);
		}

		// 色適応 
		m_BillMaterial.Diffuse = m_BillDiffuse;

		// 描画
		m_BillMesh.Draw(GetDeviceContext(), &m_BillMesh);

		SetBlendState(BS_NONE);

		// ライトオン
		Singleton<CLight>::GetInstance().SetEnable();
	}
	void UninitBill()
	{ 
		m_BillMesh.Release(&m_BillMesh); 
	}

	// セット関数
	void SetPosition(float X, float Y, float Z) { m_BillPos = XMFLOAT3(X, Y, Z); }		//座標セット
	void SetPosition(XMFLOAT3 m_Pos) { m_BillPos = m_Pos; }
	void SetSize(float SizeX, float SizeY) { m_BillSize = XMFLOAT2(SizeX, SizeY); }				//サイズセット
	void SetSize(XMFLOAT2 size) { m_BillSize = size; }
	void SetAngle(float Angle) { m_BillAngleY = Angle; }							//角度セット
	void SetUV(float U, float V) { m_BillUV = XMFLOAT2(U, V); }					//テクスチャ座標セット
	void SetUV(XMFLOAT2 uv) { m_BillUV = uv; }
	void SetFrameSize(float TexSizeX, float TexSizeY) { m_BillFrameSize = XMFLOAT2(TexSizeX, TexSizeY); }	//テクスチャフレームサイズセット
	void SetTex(ID3D11ShaderResourceView* tex) { m_BillMesh.m_pTexture = tex; }

	void SetBillFrameNum(XMINT2 frame) 
	{
		m_isBillFrameInit = true;
		m_BillFrameNum = frame;
		m_BillFrameSize.x = 1.0f / m_BillFrameNum.x;
		m_BillFrameSize.y = 1.0f / m_BillFrameNum.y;
	}
	void SetBillDiffuse(XMFLOAT4 dif) { m_BillDiffuse = dif; }

	// ゲット関数
	XMFLOAT3 GetBillPos() { return m_BillPos; }
	XMFLOAT2 GetBillSize() { return m_BillSize; }

	//MESH m_BillMesh;
	CMesh m_BillMesh;

private:
	// メンバ変数
	MATERIAL m_BillMaterial;
	XMFLOAT3 m_BillPos;
	XMFLOAT2 m_BillSize;
	XMFLOAT2 m_BillUV;
	XMFLOAT2 m_BillFrameSize;
	float m_BillAngleY;
	bool m_isBillInit;
	XMFLOAT4 m_BillDiffuse;

	bool m_isBillFrameInit;
	XMINT2 m_BillFrameNum;

};

