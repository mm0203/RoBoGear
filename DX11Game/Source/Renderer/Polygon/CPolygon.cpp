//=============================================================================
// CPolygon.cpp
//=============================================================================
// Author  松野 将之
//=============================================================================
#include "CPolygon.h"

//=============================================================================
// 
// コンストラクタ
// 
//=============================================================================
CPolygon::CPolygon()
{
	Init();
}

//=============================================================================
// 
// デストラクタ
// 
//=============================================================================
CPolygon::~CPolygon()
{
	if (m_pTex && m_isLoadTex) SAFE_RELEASE(m_pTex);
}

//=============================================================================
// 
// 初期化処理
// 
//=============================================================================
void CPolygon::Init()
{
	// メンバ変数初期化
	m_pTex = nullptr;
	m_Pos = XMFLOAT2(0.0f, 0.0f);
	m_Size = XMFLOAT2(1.0f, 1.0f);
	m_UV = XMFLOAT2(0.0f, 0.0f);
	m_FrameSize = XMFLOAT2(1.0f, 1.0f);
	m_PolygonAngle = 0.0f;
	m_Alpha = 1.0f;
	m_Color = XMFLOAT3(1.0f, 1.0f, 1.0f);
}

//=============================================================================
// 
// 描画処理
// 
//=============================================================================
void CPolygon::Draw()
{
	SetBlendState(BS_ALPHABLEND);
	CSingleton<CGraphics>::GetInstance().SetDepthStencilState(DEPTHSTENCIL_OFF);
	//SetZBuffer(false);
	// ポリゴン情報セット
	if (m_pTex != nullptr)	SetPolygonTexture(m_pTex);
	else SetPolygonTexture(nullptr);
	SetPolygonPos(m_Pos.x, m_Pos.y);
	SetPolygonSize(m_Size.x, m_Size.y);
	SetPolygonAngle(m_PolygonAngle);
	SetPolygonUV(m_UV.x, m_UV.y);
	SetPolygonFrameSize(m_FrameSize.x, m_FrameSize.y);
	SetPolygonColor(m_Color.x, m_Color.y, m_Color.z);
	SetPolygonAlpha(m_Alpha);
	// 描画
	DrawPolygon(GetDeviceContext());
	//SetZWrite(true);
	CSingleton<CGraphics>::GetInstance().SetDepthStencilState(DEPTHSTENCIL_ON);
	SetBlendState(BS_NONE);
}

//=============================================================================
// 
// テクスチャロード
// 
//=============================================================================
HRESULT CPolygon::LoadTexture(const wchar_t* FileName)
{
	HRESULT hr = S_OK;
	hr = CreateTextureFromFile(GetDevice(), FileName, &m_pTex);
	m_isLoadTex = true;
	return hr;
}

//=============================================================================
// 
// テクスチャロード
// 
//=============================================================================
HRESULT CPolygon::LoadTexture(const char* FileName)
{
	HRESULT hr = S_OK;
	hr = CreateTextureFromFile(GetDevice(), FileName, &m_pTex);
	m_isLoadTex = true;
	return hr;
}