//=============================================================================
// CPolygon.h
//=============================================================================
// Author  松野 将之
//=============================================================================
#pragma once

#include "polygon.h"
#include <main.h>
#include <Renderer/Texture/Texture.h>
#include <Renderer/Graphics/Graphics.h>
#include <System/Singleton/singleton.h>



//=============================================================================
// 
// クラス定義
// 
//=============================================================================
class CPolygon
{
public:
	// コンストラクタ
	CPolygon()
	{
		Init();
	}

	// デストラクタ
	~CPolygon()
	{ 
		if (m_pTex && m_isLoadTex) SAFE_RELEASE(m_pTex); 
	}

public:
	void Init()
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
	void Draw()
	{
		Singleton<Graphics>::GetInstance().SetDepthStencilState(DEPTHSTENCIL_OFF);
		//SetZBuffer(false);
		SetBlendState(BS_ALPHABLEND);
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
		Singleton<Graphics>::GetInstance().SetDepthStencilState(DEPTHSTENCIL_ON);
		SetBlendState(BS_NONE);
	}
public:
	// getter
	XMFLOAT2 GetPos() { return m_Pos; }//座標
	XMFLOAT2 GetSize() { return m_Size; }//サイズ
	float GetAngle() { return m_PolygonAngle; }		// ポリゴンの角度
	XMFLOAT2 GetUN() { return m_UV; }				// UV座標
	XMFLOAT2 GetFrameSize() { return m_FrameSize; }	// UVサイズ
	XMFLOAT3 GetColor() { return m_Color; }			// 色
	float GetAlpha() { return m_Alpha; }			// α値

	// setter
	HRESULT LoadTexture(const wchar_t* FileName)	//テクスチャロード
	{
		HRESULT hr = S_OK;
		hr = CreateTextureFromFile(GetDevice(), FileName, &m_pTex);
		m_isLoadTex = true;
		return hr;
	}
	HRESULT LoadTexture(const char* FileName)	//テクスチャロード
	{
		HRESULT hr = S_OK;
		hr = CreateTextureFromFile(GetDevice(), FileName, &m_pTex);
		m_isLoadTex = true;
		return hr;
	}

	void SetPosition(float X, float Y) { m_Pos = XMFLOAT2(X, Y); }	//座標セット
	void SetPosition(XMFLOAT2 pos) { m_Pos = pos; }
	void SetSize(float SizeX, float SizeY) { m_Size = XMFLOAT2(SizeX, SizeY); }	//サイズセット
	void SetSize(XMFLOAT2 size) { m_Size = size; }
	void SetAngle(float Angle) { m_PolygonAngle = Angle; }		//角度セット
	void SetUV(float U, float V) { m_UV = XMFLOAT2(U, V); }		//テクスチャ座標セット
	void SetUV(XMFLOAT2 uv) { m_UV = uv; }
	void SetFrameSize(float TexSizeX, float TexSizeY) { m_FrameSize = XMFLOAT2(TexSizeX, TexSizeY); }	//テクスチャフレームサイズセット
	void SetColor(float r, float g, float b) { m_Color = XMFLOAT3(r, g, b); }	//色セット
	void SetColor(XMFLOAT3 color) { m_Color = color; }
	void SetAlpha(float Alpha) { m_Alpha = Alpha; }		//アルファ値セット
	void SetRGBA(XMFLOAT4 rgba) { m_Color = XMFLOAT3(rgba.x, rgba.y, rgba.y); m_Alpha = rgba.w; }
	void SetTex(ID3D11ShaderResourceView* tex) { m_pTex = tex; }


private:
	ID3D11ShaderResourceView* m_pTex;	//テクスチャ
	XMFLOAT2 m_Pos;						//座標
	XMFLOAT2 m_Size;					//サイズ
	float m_PolygonAngle;				//ポリゴンの角度
	XMFLOAT2 m_UV;						//UV座標
	XMFLOAT2 m_FrameSize;				//UVサイズ
	XMFLOAT3 m_Color;					//色
	float m_Alpha;						//α値
	bool m_isLoadTex = false;
};