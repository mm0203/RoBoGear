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
class Sprite
{
public:
	Sprite() = default;
	virtual ~Sprite() = default;

	friend class SpriteManager; // フレンドクラス

	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update(GameState state) = 0;
	virtual void Draw(GameState state) = 0;

protected:
};