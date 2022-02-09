//=============================================================================
// SpriteManager.h
//=============================================================================
// Author  松野 将之
//=============================================================================
#pragma once

#include "Sprite.h"
#include "GameManager.h"

#include <vector>
#include <memory>
#include <string>

//=============================================================================
// 
// クラス定義
// 
//=============================================================================

// 前方宣言
class Sprite;

// 型定義
typedef std::shared_ptr<Sprite> sprite_shared;
typedef std::weak_ptr<Sprite> sprite_weak;

class SpriteManager
{
public:
	SpriteManager() = default;
	~SpriteManager() = default;

	// スプライト生成
	template<class T>
	static sprite_shared CreateSprite()
	{
		sprite_shared ptr;
		ptr.reset(new T());

		// スプライトリストに追加
		AddSpriteList(ptr);
		return ptr;
	}

	// オブジェクトリストに追加
	static void AddSpriteList(const sprite_shared& pObj)
	{
		m_pSpriteList.emplace_back(pObj);
	}

	static void InitAll();	 // 全初期化
	static void UninitAll(); // 全終了
	static void UpdateAll(GameState state); // 全更新
	static void DrawAll(GameState state);	// 全描画


private:
	static std::vector<sprite_shared> m_pSpriteList; // インスタンス格納用リスト

};