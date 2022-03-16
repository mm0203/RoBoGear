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
typedef std::shared_ptr<CObject> obj_shared;
typedef std::weak_ptr<CObject> obj_weak;

class CObjectManager
{
public:
	CObjectManager() = default;
	~CObjectManager() = default;

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
		m_ActiveList.emplace_back(pObj);
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
	static std::weak_ptr<CObject> SearchObjectTag(std::string tag);
	// 使用リストから移動オブジェクト取得
	static std::weak_ptr<CObject> GetObjectAtPosition(std::string tag ,XMINT2 pos);
	// 未使用リストから移動オブジェクト取得
	static std::weak_ptr<CObject> GetUnusedObjectAtPosition(std::string tag, XMINT2 pos);
	// オブジェクトチェック
	static bool IsObject(std::string tag, XMINT2 pos);
	// 未使用リストから使用リストに移す
	static void UnusedToActive(std::string tag);

private:
	// インスタンス使用リスト
	static std::list<obj_shared> m_ActiveList;
	// インスタンス未使用リスト
	static std::list<obj_shared> m_UnusedList;

};