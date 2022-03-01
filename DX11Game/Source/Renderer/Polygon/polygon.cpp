//=============================================================================
// polygon.cpp
//=============================================================================
// Author  松野 将之
//=============================================================================

#include "polygon.h"
#include <Renderer/Graphics/Graphics.h>
#include <System/Singleton/singleton.h>
#include <Renderer/Shader/Script/Shader.h>
#include <Renderer/Shader/Script/ShaderList.h>

//=============================================================================
// 
// 構造体定義
// 
//=============================================================================
// シェーダに渡す値
struct SHADER_GLOBAL 
{
	XMMATRIX	mWorld;		// ワールド変換行列(転置行列)
	XMMATRIX	mView;		// ビュー変換行列(転置行列)
	XMMATRIX	mProj;		// 射影変換行列(転置行列)
	XMMATRIX	mTex;		// テクスチャ変換行列(転置行列)
};

//=============================================================================
// 
// プロトタイプ宣言
// 
//=============================================================================
static HRESULT MakeVertexPolygon();
static void SetVertexPolygon();

//=============================================================================
// 
// グローバル変数
// 
//=============================================================================
static ID3D11ShaderResourceView*	g_pTexture;		// テクスチャへのポインタ

static VERTEX_2D	g_vertexWk[NUM_VERTEX];	// 頂点情報格納ワーク

static XMFLOAT3		g_posPolygon;	// ポリゴンの移動量
static XMFLOAT3		g_rotPolygon;	// ポリゴンの回転量
static XMFLOAT3		g_sizPolygon;	// ポリゴンのサイズ
static XMFLOAT4		g_colPolygon;	// ポリゴンの頂点カラー
static bool			g_bInvalidate;	// 頂点データ更新フラグ

static XMFLOAT2		g_posTexFrame;	// UV座標
static XMFLOAT2		g_sizTexFrame;	// テクスチャ抽出サイズ

ConstantBuffer*		g_pMeshCBuffer; // 定数バッファ
DXBuffer*			g_pMeshBuffer;  // メッシュバッファ

static XMFLOAT4X4	g_mProj;		// 射影変換行列
static XMFLOAT4X4	g_mView;		// ビュー変換行列
static XMFLOAT4X4	g_mWorld;		// ワールド変換行列
static XMFLOAT4X4	g_mTex;			// テクスチャ変換行列

//=============================================================================
// 
// 初期化処理
// 
//=============================================================================
HRESULT InitPolygon()
{
	HRESULT hr = S_OK;

	g_pMeshCBuffer = nullptr;
	g_pMeshBuffer = nullptr;

	// 定数バッファ生成
	g_pMeshCBuffer = new ConstantBuffer;
	g_pMeshCBuffer->Create(sizeof(SHADER_GLOBAL));

	// 変換行列初期化
	XMStoreFloat4x4(&g_mWorld, XMMatrixIdentity());
	XMStoreFloat4x4(&g_mView, XMMatrixLookAtLH(XMVectorSet(0.0f, 0.0f, -10.0f, 1.0f),
		XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)));
	XMStoreFloat4x4(&g_mProj, XMMatrixOrthographicLH(SCREEN_WIDTH, SCREEN_HEIGHT, 1.0f, 100.0f));
	XMStoreFloat4x4(&g_mTex, XMMatrixIdentity());
	g_mTex._44 = 0.0f;

	// 各情報の初期化
	g_posPolygon = XMFLOAT3(0.0f, 0.0f, 0.0f);
	g_rotPolygon = XMFLOAT3(0.0f, 0.0f, 0.0f);
	g_sizPolygon = XMFLOAT3(1.0f, 1.0f, 1.0f);
	g_colPolygon = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	g_bInvalidate = false;

	g_posTexFrame = XMFLOAT2(0.0f, 0.0f);
	g_sizTexFrame = XMFLOAT2(1.0f, 1.0f);

	// 頂点情報の作成
	hr = MakeVertexPolygon();

	return hr;
}

//=============================================================================
// 
// 終了処理
// 
//=============================================================================
void UninitPolygon()
{
	SAFE_RELEASE(g_pTexture);
	SAFE_DELETE(g_pMeshCBuffer);
	SAFE_DELETE(g_pMeshBuffer);
}

//=============================================================================
// 
// 更新処理
// 
//=============================================================================
void UpdatePolygon()
{

}

//=============================================================================
// 
// 描画処理
// 
//=============================================================================
void DrawPolygon(ID3D11DeviceContext* pDeviceContext)
{
	// 拡縮
	XMMATRIX mWorld = XMMatrixScaling(g_sizPolygon.x, g_sizPolygon.y, g_sizPolygon.z);
	// 回転
	mWorld *= XMMatrixRotationRollPitchYaw(XMConvertToRadians(g_rotPolygon.x), XMConvertToRadians(g_rotPolygon.y), XMConvertToRadians(g_rotPolygon.z));
	// 移動
	mWorld *= XMMatrixTranslation(g_posPolygon.x, g_posPolygon.y, g_posPolygon.z);

	// ワールド マトリックスに設定
	XMStoreFloat4x4(&g_mWorld, mWorld);

	if (g_pTexture)
	{
		// 拡縮
		mWorld = XMMatrixScaling(g_sizTexFrame.x, g_sizTexFrame.y, 1.0f);
		// 移動
		mWorld *= XMMatrixTranslation(g_posTexFrame.x, g_posTexFrame.y, 0.0f);
		// テクスチャ マトリックスに設定
		XMStoreFloat4x4(&g_mTex, mWorld);
	} 
	else 
	{
		// テクスチャ無し
		g_mTex._44 = 0.0f;
	}

	// 頂点バッファ更新
	SetVertexPolygon();

	// シェーダセット
	GetVertexShader(POLYGON_VS)->Bind();
	GetPixelShader(POLYGON_PS)->Bind();

	// サンプラセット
	Singleton<Graphics>::GetInstance().SetSamplerState(SAMPLER_POINT);

	// テクスチャセット
	pDeviceContext->PSSetShaderResources(0, 1, &g_pTexture);

	SHADER_GLOBAL cb;
	cb.mProj = XMMatrixTranspose(XMLoadFloat4x4(&g_mProj));
	cb.mView = XMMatrixTranspose(XMLoadFloat4x4(&g_mView));
	cb.mWorld = XMMatrixTranspose(XMLoadFloat4x4(&g_mWorld));
	cb.mTex = XMMatrixTranspose(XMLoadFloat4x4(&g_mTex));

	// バッファ更新
	g_pMeshCBuffer->Write(&cb);
	g_pMeshCBuffer->BindVS(0);
	g_pMeshCBuffer->BindPS(0);

	// ポリゴン描画
	g_pMeshBuffer->Draw(NUM_VERTEX);
}

//=============================================================================
// 
// 頂点の作成
// 
//=============================================================================
HRESULT MakeVertexPolygon()
{
	// 頂点座標の設定
	g_vertexWk[0].vtx = XMFLOAT3(-0.5f,  0.5f, 0.0f);
	g_vertexWk[1].vtx = XMFLOAT3( 0.5f,  0.5f, 0.0f);
	g_vertexWk[2].vtx = XMFLOAT3(-0.5f, -0.5f, 0.0f);
	g_vertexWk[3].vtx = XMFLOAT3( 0.5f, -0.5f, 0.0f);

	// 拡散反射光の設定
	g_vertexWk[0].diffuse = g_colPolygon;
	g_vertexWk[1].diffuse = g_colPolygon;
	g_vertexWk[2].diffuse = g_colPolygon;
	g_vertexWk[3].diffuse = g_colPolygon;

	// テクスチャ座標の設定
	g_vertexWk[0].tex = XMFLOAT2(0.0f, 0.0f);
	g_vertexWk[1].tex = XMFLOAT2(1.0f, 0.0f);
	g_vertexWk[2].tex = XMFLOAT2(0.0f, 1.0f);
	g_vertexWk[3].tex = XMFLOAT2(1.0f, 1.0f);

	// 頂点&インデックスバッファ 生成
	DXBuffer::Desc desc;
	desc.vtxSize = sizeof(VERTEX_2D);
	desc.vtxCount = NUM_VERTEX;
	desc.idxSize = sizeof(int);
	desc.isWrite = true;
	desc.pVtx = &g_vertexWk[0];
	desc.pIdx = nullptr;
	desc.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;

	g_pMeshBuffer = new DXBuffer();
	HRESULT hr = g_pMeshBuffer->Create(desc);
	if (FAILED(hr)) { return hr; }

	return hr;
}

//=============================================================================
// 
// 頂点座標の設定
// 
//=============================================================================
void SetVertexPolygon()
{
	if (g_bInvalidate) 
	{
		//頂点バッファの中身を埋める
		ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
		HRESULT hr = S_OK;

		// 拡散反射光の設定
		g_vertexWk[0].diffuse = g_colPolygon;
		g_vertexWk[1].diffuse = g_colPolygon;
		g_vertexWk[2].diffuse = g_colPolygon;
		g_vertexWk[3].diffuse = g_colPolygon;

		// 頂点データ書き込み
		g_pMeshBuffer->Write(g_vertexWk);

		// フラグをクリア
		g_bInvalidate = false;
	}
}

//=============================================================================
// 
// テクスチャの設定
// 
//=============================================================================
void SetPolygonTexture(ID3D11ShaderResourceView* pTexture)
{
	g_pTexture = pTexture;
	g_mTex._44 = (g_pTexture) ? 1.0f : 0.0f;
}

//=============================================================================
// 
// 表示座標の設定
// 
//=============================================================================
void SetPolygonPos(float fX, float fY)
{
	g_posPolygon.x = fX;
	g_posPolygon.y = fY;
}

//=============================================================================
// 
// 表示サイズの設定
// 
//=============================================================================
void SetPolygonSize(float fScaleX, float fScaleY)
{
	g_sizPolygon.x = fScaleX;
	g_sizPolygon.y = fScaleY;
}

//=============================================================================
// 
// 表示角度の設定(単位:度)
// 
//=============================================================================
void SetPolygonAngle(float fAngle)
{
	g_rotPolygon.z = fAngle;
}

//=============================================================================
// 
// 左上テクスチャ座標の設定 (0.0≦fU＜1.0, 0.0≦fV＜1.0)
// 
//=============================================================================
void SetPolygonUV(float fU, float fV)
{
	g_posTexFrame.x = fU;
	g_posTexFrame.y = fV;
}

//=============================================================================
// 
// テクスチャフレームサイズの設定 (0.0＜fWidth≦1.0, 0.0＜fHeight≦1.0)
// 
//=============================================================================
void SetPolygonFrameSize(float fWidth, float fHeight)
{
	g_sizTexFrame.x = fWidth;
	g_sizTexFrame.y = fHeight;
}

//=============================================================================
// 
// 頂点カラーの設定
// 
//=============================================================================
void SetPolygonColor(float fRed, float fGreen, float fBlue)
{
	if (fRed != g_colPolygon.x || fGreen != g_colPolygon.y || fBlue != g_colPolygon.z)
	{
		g_colPolygon.x = fRed;
		g_colPolygon.y = fGreen;
		g_colPolygon.z = fBlue;
		g_bInvalidate = true;
	}
}

//=============================================================================
// 
// 不透明度の設定
// 
//=============================================================================
void SetPolygonAlpha(float fAlpha)
{
	if (fAlpha != g_colPolygon.w)
	{
		g_colPolygon.w = fAlpha;
		g_bInvalidate = true;
	}
}