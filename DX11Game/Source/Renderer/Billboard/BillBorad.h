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

//=============================================================================
// 
// クラス定義
// 
//=============================================================================
class BillBoard
{
public:
	BillBoard();
	~BillBoard() = default;

public:
	void Init();
	void Update();
	void Draw(int AnimNum = 0);
	void Uninit();

	// テクスチャロード
	HRESULT LoadBillTexture(const wchar_t* FileName);
	HRESULT LoadBillTexture(const char* FileName);

	// setter 

	// 座標セット
	void SetPosition(float X, float Y, float Z) { m_BillPos = XMFLOAT3(X, Y, Z); }	
	void SetPosition(XMFLOAT3 m_Pos) { m_BillPos = m_Pos; }
	// サイズセット
	void SetSize(float SizeX, float SizeY) { m_BillSize = XMFLOAT2(SizeX, SizeY); }	
	void SetSize(XMFLOAT2 size) { m_BillSize = size; }
	// 角度セット
	void SetAngle(float Angle) { m_BillAngleY = Angle; }
	// テクスチャ座標セット
	void SetUV(float U, float V) { m_BillUV = XMFLOAT2(U, V); }
	void SetUV(XMFLOAT2 uv) { m_BillUV = uv; }
	// テクスチャフレームサイズセット
	void SetFrameSize(float TexSizeX, float TexSizeY) { m_BillFrameSize = XMFLOAT2(TexSizeX, TexSizeY); }
	// void SetTex(ID3D11ShaderResourceView* tex) { m_BillMesh.m_pTexture = tex; }

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

protected:
	CMesh m_BillMesh;			// ビルボード用メッシュ

private:
	MATERIAL m_BillMaterial;	// マテリアル
	XMFLOAT3 m_BillPos;			// 位置
	XMFLOAT2 m_BillSize;		// サイズ
	XMFLOAT2 m_BillUV;			// UV座標
	XMFLOAT2 m_BillFrameSize;	// フレームサイズ
	float m_BillAngleY;			// 角度
	bool m_isBillInit;			// 初期化判定
	XMFLOAT4 m_BillDiffuse;		// デフューズカラー
	bool m_isBillFrameInit;		// フレーム初期化判定
	XMINT2 m_BillFrameNum;		// フレーム数

};

