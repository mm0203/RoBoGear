//=============================================================================
// ObjectManager.h
//=============================================================================
// Author  松野 将之
//=============================================================================
#pragma once

#include "Object.h"
#include <Component/Transform.h>
#include <Renderer/Renderer.h>
#include <vector>
#include <list>
#include <memory>
#include <string>

//=============================================================================
// 
// クラス定義
// 
//=============================================================================
// 型定義
typedef std::shared_ptr<Object> obj_shared;
typedef std::weak_ptr<Object> obj_weak;

class ObjectManager
{
public:
	ObjectManager() = default;
	~ObjectManager() = default;

	// オブジェクト生成
	template<class T>
	static obj_shared CreateObject(
		XMFLOAT3 pos = XMFLOAT3(0, 0, 0), 
		XMINT2 coord = XMINT2(0, 0),
		XMFLOAT3 scale = XMFLOAT3(1.0f, 1.0f, 1.0f),
		XMFLOAT3 rot = XMFLOAT3(0, 0, 0))
	{
		obj_shared ptr;
		ptr.reset(new T());

		// インスタンス生成時に情報をセット
		ptr->m_Pos = pos;
		ptr->m_Coord = coord;
		ptr->m_Scale = scale;
		ptr->m_Rot = rot;

		// オブジェクトリストに追加
		AddObjList(ptr);
		return ptr;
	}

	// オブジェクトリストに追加
	static void AddObjList(const obj_shared& pObj)
	{
		m_pObjList.emplace_back(pObj);
	}

	static void InitAll();	 // 全初期化
	static void UninitAll(); // 全終了
	static void UpdateAll(); // 全更新
	static void DrawAll();	 // 全描画

	// オブジェクト削除
	static void DestroyObject(std::string tag);
	// オブジェクト削除(エディット用)
	static bool DestroyEditObject(std::string tag, XMINT2 pos);
	// タグサーチ
	static std::weak_ptr<Object> SearchObjectTag(std::string tag);
	// 移動オブジェクト取得
	static std::weak_ptr<Object> GetObjectAtPosition(std::string tag ,XMINT2 pos);
	// オブジェクトチェック
	static bool IsObject(std::string tag, XMINT2 pos);

private:
	//static std::vector<obj_shared> m_pObjList; // インスタンス格納用リスト
	static std::list<obj_shared> m_pObjList; // インスタンス格納用リスト

};