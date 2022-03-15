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
	CPolygon();
	~CPolygon();

	void Init();
	void Draw();

	// テクスチャロード
	HRESULT LoadTexture(const wchar_t* FileName);
	HRESULT LoadTexture(const char* FileName);

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
	// 座標
	void SetPosition(float X, float Y) { m_Pos = XMFLOAT2(X, Y); }
	void SetPosition(XMFLOAT2 pos) { m_Pos = pos; }
	// サイズ
	void SetSize(float SizeX, float SizeY) { m_Size = XMFLOAT2(SizeX, SizeY); }
	void SetSize(XMFLOAT2 size) { m_Size = size; }
	// 角度
	void SetAngle(float Angle) { m_PolygonAngle = Angle; }
	// テクスチャ座標
	void SetUV(float U, float V) { m_UV = XMFLOAT2(U, V); }
	void SetUV(XMFLOAT2 uv) { m_UV = uv; }
	// テクスチャフレームサイズ
	void SetFrameSize(float TexSizeX, float TexSizeY) { m_FrameSize = XMFLOAT2(TexSizeX, TexSizeY); }
	// 色
	void SetColor(float r, float g, float b) { m_Color = XMFLOAT3(r, g, b); }
	void SetColor(XMFLOAT3 color) { m_Color = color; }
	// 不透明度
	void SetAlpha(float Alpha) { m_Alpha = Alpha; }
	void SetRGBA(XMFLOAT4 rgba) { m_Color = XMFLOAT3(rgba.x, rgba.y, rgba.y); m_Alpha = rgba.w; }
	// テクスチャ
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