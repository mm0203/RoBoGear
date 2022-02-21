#pragma once
//=============================================================================
// Transform.h
//=============================================================================
// Author  松野 将之
//=============================================================================
#pragma once

//=============================================================================
// 
// インクルード部
// 
//=============================================================================
#include <main.h>

//=============================================================================
// 
// クラス定義
// 
//=============================================================================

// オブジェクトクラス
class CTransform
{
public:
	CTransform()
	{
		m_Pos = XMFLOAT3{ 0.0f, 0.0f, 0.0f };
		m_Coord = XMINT2{ 0,0 };
		m_Scale = XMFLOAT3{ 0.0f, 0.0f, 0.0f };
		m_Rot = XMFLOAT3{ 0.0f, 0.0f, 0.0f };
		m_Move = XMFLOAT3{ 0.0f, 0.0f, 0.0f };
	}

	~CTransform() = default;

	// getter
	XMFLOAT3& GetPos() { return m_Pos; }
	XMINT2&  GetCoord() { return m_Coord; }
	XMFLOAT3& GetScale() { return m_Scale; }
	XMFLOAT3& GetRot() { return m_Rot; }
	XMFLOAT3& GetMove() { return m_Move; }

	// setter
	void SetPos(XMFLOAT3 pos) { m_Pos = pos; }
	void SetCoord(XMINT2 coord) { m_Coord = coord; }
	void SetScale(XMFLOAT3 scale) { m_Scale = scale; }
	void SetRot(XMFLOAT3 rot) { m_Rot = rot; }
	void SetMove(XMFLOAT3 move) { m_Move = move; }

protected:
	XMFLOAT3 m_Pos;		// 位置
	XMINT2   m_Coord;	// 座標
	XMFLOAT3 m_Scale;	// サイズ
	XMFLOAT3 m_Rot;		// 回転
	XMFLOAT3 m_Move;	// 移動量
};