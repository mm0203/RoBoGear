//=============================================================================
// Object.h
//=============================================================================
// Author  松野 将之
//=============================================================================
#pragma once

#include <Component/Transform.h>
#include <Renderer/Renderer.h>

#include <vector>
#include <memory>
#include <string>

//=============================================================================
// 
// クラス定義
// 
//=============================================================================
// オブジェクトクラス
class CObject
{
public:
	CObject();
	virtual ~CObject() = default;

	friend class CObjectManager; // フレンドクラス

	virtual void Init() = 0;
	virtual void Uninit();
	virtual void Update() = 0;
	virtual void Draw();

	// getter
	//CTransform& GetTransform() { return m_Transform; }
	XMFLOAT3 GetPos() { return m_Pos; }
	XMINT2  GetCoord() { return m_Coord; }
	XMFLOAT3 GetScale() { return m_Scale; }
	XMFLOAT3 GetRot() { return m_Rot; }
	XMFLOAT3& GetMove() { return m_Move; }
	std::string GetTag() { return m_tag; }
	CRenderer& GetModel() { return m_Model; }

	// setter
	void SetPos(XMFLOAT3 pos) { m_Pos = pos; }
	void SetCoord(XMINT2 coord) { m_Coord = coord; }
	void SetScale(XMFLOAT3 scale) { m_Scale = scale; }
	void SetRot(XMFLOAT3 rot) { m_Rot = rot; }
	void SetMove(XMFLOAT3 move) { m_Move = move; }

	// オブジェクトの慣性移動
	void ObjectMove();

protected:
	// オブジェクトの情報
	//CTransform m_Transform;

	XMFLOAT3 m_Pos;		// 位置
	XMINT2   m_Coord;	// 座標
	XMFLOAT3 m_Scale;	// サイズ
	XMFLOAT3 m_Rot;		// 回転
	XMFLOAT3 m_Move;	// 移動量
	std::string m_tag;	// タグ名
	CRenderer m_Model;	// モデル情報
};