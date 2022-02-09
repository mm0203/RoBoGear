//=============================================================================
// Sprite.h
//=============================================================================
// Author  ���� ���V
//=============================================================================
#pragma once

#include "SpriteManager.h"
#include "GameManager.h"

//=============================================================================
// 
// �N���X��`
// 
//=============================================================================
class Sprite
{
public:
	Sprite() = default;
	virtual ~Sprite() = default;

	friend class SpriteManager; // �t�����h�N���X

	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update(GameState state) = 0;
	virtual void Draw(GameState state) = 0;

protected:
};