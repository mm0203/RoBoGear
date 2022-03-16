//=============================================================================
// ObjectManager.cpp
//=============================================================================
// Author  松野 将之
// 
//=============================================================================

#include "ObjectManager.h"

//=============================================================================
// 
// 静的メンバ
// 
//=============================================================================
std::list<obj_shared> CObjectManager::m_ActiveList;
std::list<obj_shared> CObjectManager::m_UnusedList;

//=============================================================================
// 
// 初期化
// 
//=============================================================================
void CObjectManager::InitAll()
{
	for (auto& obj : m_ActiveList)
		obj->Init();
}

//=============================================================================
// 
// 更新
// 
//=============================================================================
void CObjectManager::UpdateAll()
{
	// 更新中に要素を削除する場合があるので範囲for文は使用できない
	for (auto it = m_ActiveList.begin(); it != m_ActiveList.end(); ++it)
		it->get()->Update();
}

//=============================================================================
// 
// 終了
// 
//=============================================================================
void CObjectManager::UninitAll()
{
	// インスタンスの数を取得
	int objCnt = (int)m_ActiveList.size();

	// インスタンスを削除
	for (int i = 0; i < objCnt; i++)
	{
		obj_shared obj;					 		   // 削除用ポインタ
		obj = *(m_ActiveList.begin());			   // 要素のポインタ
		obj->Uninit();							   // 要素の終了処理を呼ぶ
		m_ActiveList.erase(m_ActiveList.begin());  // リストから削除
	}

	// 未使用リストにあるインスタンスの数を取得
	objCnt = (int)m_UnusedList.size();

	// リスト内のインスタンスを削除
	for (int i = 0; i < objCnt; i++)
	{
		obj_shared obj;					 	       // 削除用ポインタ
		obj = *(m_UnusedList.begin());			   // 要素のポインタ
		obj->Uninit();							   // 要素の終了処理を呼ぶ
		m_UnusedList.erase(m_UnusedList.begin());  // リストから削除
	}
}

//=============================================================================
// 
// 描画
// 
//=============================================================================
void CObjectManager::DrawAll()
{
	for (auto& obj : m_ActiveList)
		obj->Draw();
}

//=============================================================================
// 
// オブジェクト削除
// 
//=============================================================================
void CObjectManager::DestroyObject(std::string tag)
{
	for (auto it = m_ActiveList.begin(); it != m_ActiveList.end(); it++)
	{
		// タグ名を取得
		if(it->get()->GetTag() == tag)
		{
			// 削除するオブジェクトを未使用リストに移す
			m_UnusedList.splice(m_UnusedList.begin(), m_ActiveList, it);
			return;

			//it->get()->Uninit();		   // 要素の終了処理を呼ぶ
			//it->reset();				   // 要素の中身を空に
			//it = m_ActiveList.erase(it); // リストから削除
		}
		//else ++it;	// イテレータの指す場所を正常に
	}
}

//=============================================================================
// 
// 未使用リストから使用リストへ
// 
//=============================================================================
void CObjectManager::UnusedToActive(std::string tag)
{
	for (auto it = m_UnusedList.begin(); it != m_UnusedList.end(); it++)
	{
		// 未使用リストから取り出す
		if (it->get()->GetTag() == tag)
		{
			// 未使用リストのオブジェクトを使用リストの末尾に
			m_ActiveList.splice(m_ActiveList.end(), m_UnusedList, it);
			return;
		}
	}
}

//=============================================================================
// 
// タグサーチ
// 
//=============================================================================
std::weak_ptr<CObject> CObjectManager::SearchObjectTag(std::string tag)
{
	for (const auto& obj : m_ActiveList)
	{
		// タグ名を取得
		if (obj->GetTag() == tag)
			return obj;
	}
	return std::weak_ptr<CObject>();
}

//=============================================================================
// 
// 使用リストから移動オブジェクト取得
// 
//=============================================================================
std::weak_ptr<CObject> CObjectManager::GetObjectAtPosition(std::string tag, XMINT2 pos)
{
	for (const auto& obj : m_ActiveList)
	{
		// タグ名を取得
		if (obj->GetTag() == tag)
		{
			// タグ名のポジションと引数のポジションが同じだったら
			if (obj->GetCoord() == pos)
				return obj;
		}
	}
	return std::weak_ptr<CObject>();
}

//=============================================================================
// 
// 未使用リストから移動オブジェクト取得
// 
//=============================================================================
std::weak_ptr<CObject> CObjectManager::GetUnusedObjectAtPosition(std::string tag, XMINT2 pos)
{
	for (const auto& obj : m_UnusedList)
	{
		// タグ名を取得
		if (obj->GetTag() == tag)
		{
			// タグ名のポジションと引数のポジションが同じだったら
			if (obj->GetCoord() == pos)
				return obj;
		}
	}
	return std::weak_ptr<CObject>();
}

//=============================================================================
// 
// オブジェクトチェック
// 
//=============================================================================
bool CObjectManager::IsObject(std::string tag, XMINT2 pos)
{
	for (const auto& obj : m_ActiveList)
	{
		// タグ名を取得
		if (obj->GetTag() == tag)
		{
			// タグ名のポジションと引数のポジションが同じだったら
			if (obj->GetCoord() == pos)
				return true;
		}
	}
	return false;
}

//=============================================================================
// 
// エディット削除
// 
//=============================================================================
bool CObjectManager::DestroyEditObject(std::string tag, XMINT2 pos)
{
	for (auto it = m_ActiveList.begin(); it != m_ActiveList.end();)
	{
		// タグ名を取得
		if (it->get()->GetTag() == tag)
		{
			// タグ名のポジションと引数のポジションが同じだったら
			if (it->get()->GetCoord() == pos)
			{
				//it->get()->Uninit();		// 要素の終了処理を呼ぶ
				it->reset();				// 要素の中身を空に
				it = m_ActiveList.erase(it);	// リストから削除
				return true;
			}
			else ++it;	// イテレータの指す場所を正常に
		}
		else ++it;
	}
	return false;
}