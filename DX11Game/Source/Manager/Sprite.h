//=============================================================================
// Sprite.h
//=============================================================================
// Author  松野 将之
//=============================================================================
#pragma once

#include "SpriteManager.h"
#include "GameManager.h"

//=============================================================================
// 
// クラス定義
// 
//=============================================================================
class CSprite
{
public:
	CSprite() = default;
	virtual ~CSprite() = default;

	friend class CSpriteManager; // フレンドクラス

	virtual void Init() = 0;
	virtual void Uninit() = 0;

	// 状態でスプライトの表示・非表示を管理
	virtual void Update(GameState state) = 0;
	virtual void Draw(GameState state) = 0;
};